#include "pch.h"
#include "EngineCore.h"
#include "ReadData.h"

ID3D11Device* ResourceManager::device = nullptr;
ID3D11DeviceContext* ResourceManager::context = nullptr;
std::map<std::wstring, std::vector<uint8_t>> ResourceManager::map_shaderBlob;

void ResourceManager::Init(DX::DeviceResources* deviceResource)
{
	ResourceManager::device = deviceResource->GetD3DDevice();
	ResourceManager::context = deviceResource->GetD3DDeviceContext();
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
