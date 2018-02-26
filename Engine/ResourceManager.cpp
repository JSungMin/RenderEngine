#include "pch.h"
#include "EngineCore.h"
#include "ReadData.h"

ID3D11Device* ResourceManager::device = nullptr;
std::map<std::wstring, std::vector<uint8_t>> ResourceManager::map_shaderBlob;

void ResourceManager::Init(ID3D11Device * device)
{
	ResourceManager::device = device;
}

HRESULT ResourceManager::LoadVertexShader(std::wstring fileName, OUT ID3D11VertexShader ** vertexShader)
{
	auto vertexShaderBlob = DX::ReadData(fileName.c_str());
	map_shaderBlob[fileName] = vertexShaderBlob;
	DX::ThrowIfFailed(
		device->CreateVertexShader(
			vertexShaderBlob.data(), 
			vertexShaderBlob.size(),
			nullptr,
			vertexShader)
	);
	return S_OK;
}

HRESULT ResourceManager::LoadPixelShader(std::wstring fileName, OUT ID3D11PixelShader ** pixelShader)
{
	auto pixelShaderBlob = DX::ReadData(fileName.c_str());
	map_shaderBlob[fileName] = pixelShaderBlob;
	DX::ThrowIfFailed(
		device->CreatePixelShader(
			pixelShaderBlob.data(),
			pixelShaderBlob.size(),
			nullptr,
			pixelShader)
	);
	return S_OK;
}

std::vector<uint8_t> ResourceManager::GetShaderBlob(std::string fileName)
{
	std::wstring name = L"";
	name.assign(fileName.begin(), fileName.end());
	
	return map_shaderBlob[name];
}

std::vector<uint8_t> ResourceManager::GetShaderBlob(std::wstring fileName)
{
	return map_shaderBlob[fileName];
}
