//--------------------------------------------------------------------------------------
// SimpleTexturePC.cpp
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "pch.h"
#include "SimpleTexturePC.h"

#include "ATGColors.h"
#include "FindMedia.h"
#include "EngineCore.h"
#include "ReadData.h"
#pragma once;

extern void ExitSample();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Sample::Sample()
{
    // Use gamma-correct rendering.
    m_deviceResources = std::make_unique<DX::DeviceResources>(DXGI_FORMAT_B8G8R8A8_UNORM_SRGB);
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Sample::Initialize(HWND window, int width, int height)
{
    m_gamePad = std::make_unique<GamePad>();

    m_keyboard = std::make_unique<Keyboard>();

    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();  	
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();
}

#pragma region Frame Update
// Executes basic render loop.
void Sample::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Sample::Update(DX::StepTimer const&)
{
    auto pad = m_gamePad->GetState(0);
    if (pad.IsConnected())
    {
        if (pad.IsViewPressed())
        {
            ExitSample();
        }
    }

    auto kb = m_keyboard->GetState();
    if (kb.Escape)
    {
        ExitSample();
    }
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Sample::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // Set input assembler state.
    context->IASetInputLayout(m_spInputLayout.Get());

    UINT strides = sizeof(VertexPositionTexture);
    UINT offsets = 0;
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->IASetVertexBuffers(0, 1, m_spVertexBuffer.GetAddressOf(), &strides, &offsets);

    context->IASetIndexBuffer(m_spIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

    // Set shaders.
    context->VSSetShader(m_spVertexShader.Get(), nullptr, 0);
    context->GSSetShader(nullptr, nullptr, 0);
    context->PSSetShader(m_spPixelShader.Get(), nullptr, 0);

    // Set texture and sampler.
    auto sampler = m_spSampler.Get();
    context->PSSetSamplers(0, 1, &sampler);

    auto texture = m_spTexture.Get();
    context->PSSetShaderResources(0, 1, &texture);

    // Draw quad.
    context->DrawIndexed(6, 0, 0);

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Sample::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    // Use linear clear color for gamma-correct rendering.
    context->ClearRenderTargetView(renderTarget, ATG::ColorsLinear::Background);

    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Sample::OnActivated()
{
}

void Sample::OnDeactivated()
{
}

void Sample::OnSuspending()
{
}

void Sample::OnResuming()
{
    m_timer.ResetElapsedTime();
}

void Sample::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();
}

// Properties
void Sample::GetDefaultSize(int& width, int& height) const
{
    width = 1280;
    height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Sample::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();

	ResourceManager::Init(device);

    // Load and create shaders.
	ResourceManager::LoadVertexShader(L"VertexShader.cso", m_spVertexShader.ReleaseAndGetAddressOf());
	ResourceManager::LoadPixelShader(L"PixelShader.cso", m_spPixelShader.ReleaseAndGetAddressOf());

	auto vsBlob = ResourceManager::GetShaderBlob("VertexShader.cso");

    DX::ThrowIfFailed(
        device->CreateInputLayout(
			VertexPositionTexture::InputElements,
			VertexPositionTexture::InputElementCount,
			vsBlob.data(), vsBlob.size(),
            m_spInputLayout.ReleaseAndGetAddressOf()));

    // Create vertex buffer.
    static const VertexPositionTexture s_vertexData[4] =
    {
        { XMFLOAT3( -0.5f, -0.5f, 0.5f ), XMFLOAT2( 0.f, 1.f ) },
        { XMFLOAT3(  0.5f, -0.5f, 0.5f ), XMFLOAT2( 1.f, 1.f ) },
        { XMFLOAT3(  0.5f,  0.5f, 0.5f ), XMFLOAT2( 1.f, 0.f ) },
        { XMFLOAT3( -0.5f,  0.5f, 0.5f ), XMFLOAT2( 0.f, 0.f ) },
    };

    D3D11_SUBRESOURCE_DATA initialData = {};
    initialData.pSysMem = s_vertexData;

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.ByteWidth = sizeof(s_vertexData);
    bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.StructureByteStride = sizeof(VertexPositionTexture);

    DX::ThrowIfFailed(
        device->CreateBuffer(&bufferDesc, &initialData,
            m_spVertexBuffer.ReleaseAndGetAddressOf()));

    // Create index buffer.
    static const uint16_t s_indexData[6] =
    {
        3,1,0,
        2,1,3,
    };

    initialData.pSysMem = s_indexData;

    bufferDesc.ByteWidth = sizeof(s_indexData);
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.StructureByteStride = sizeof(uint16_t);

    DX::ThrowIfFailed(
        device->CreateBuffer(&bufferDesc, &initialData,
            m_spIndexBuffer.ReleaseAndGetAddressOf()));
	/*___________________________
	Texture Component Property Block
	--Sampler
	--WICTextureSRV
	_____________________________*/
    // Create sampler.
    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    DX::ThrowIfFailed(
        device->CreateSamplerState(&samplerDesc,
            m_spSampler.ReleaseAndGetAddressOf()));

	std::wstring fileName = L"..\\Media\\Textures\\sunset.jpg";
	ID3D11Resource* wicTextureResource;

	DX::ThrowIfFailed (
		CreateWICTextureFromFile(device, fileName.c_str(), &wicTextureResource, m_spTexture.ReleaseAndGetAddressOf())
	);
}

// Allocate all memory resources that change on a window SizeChanged event.
void Sample::CreateWindowSizeDependentResources()
{
}

void Sample::OnDeviceLost()
{
    m_spInputLayout.Reset();
    m_spVertexBuffer.Reset();
    m_spIndexBuffer.Reset();
    m_spVertexShader.Reset();
    m_spPixelShader.Reset();
    m_spSampler.Reset();
    m_spTexture.Reset();
}

void Sample::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
