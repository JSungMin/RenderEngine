#include "pch.h"
#include "Texture.h"
#include "ResourceManager.h"
using Microsoft::WRL::ComPtr;

ComPtr<ID3D11SamplerState> Texture::CreateDefaultSampler()
{
	auto device = ResourceManager::GetDevice();
	ComPtr<ID3D11SamplerState> sampler;
	// Create Default sampler.
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
			sampler.ReleaseAndGetAddressOf()));
	return sampler;
}

void Texture::UpdateSampler(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE u, D3D11_TEXTURE_ADDRESS_MODE v, D3D11_TEXTURE_ADDRESS_MODE w)
{
	auto device = ResourceManager::GetDevice();
	this->sampler.Reset();

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = filter;
	samplerDesc.AddressU = u;
	samplerDesc.AddressV = v;
	samplerDesc.AddressW = w;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	DX::ThrowIfFailed(
		device->CreateSamplerState(&samplerDesc,
			this->sampler.ReleaseAndGetAddressOf()));	
}

Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture::CreateDefaultTexture(int width, int height, DXGI_FORMAT format, D3D11_BIND_FLAG bind)
{
	return Microsoft::WRL::ComPtr<ID3D11Texture2D>();
}

Microsoft::WRL::ComPtr<ID3D11Texture3D> Texture::CreateDefaultTexture(int widht, int height, int depth, DXGI_FORMAT format, D3D11_BIND_FLAG bind)
{
	return Microsoft::WRL::ComPtr<ID3D11Texture3D>();
}

Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture::CreateDynamicTexture(int width, int height, DXGI_FORMAT format, D3D11_BIND_FLAG bind)
{
	return Microsoft::WRL::ComPtr<ID3D11Texture2D>();
}

Microsoft::WRL::ComPtr<ID3D11Texture3D> Texture::CreateDynamicTexture(int width, int height, int depth, DXGI_FORMAT format, D3D11_BIND_FLAG bind)
{
	return Microsoft::WRL::ComPtr<ID3D11Texture3D>();
}
