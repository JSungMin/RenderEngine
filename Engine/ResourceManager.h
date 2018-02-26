#include "pch.h"
#include <map>
#include "DeviceResources.h"
#include "ReadData.h"
#pragma once

class ResourceManager
{
public:
	ResourceManager(DX::DeviceResources* device)
	{
		Init(device);
	}
public:
	static void Init(DX::DeviceResources* deviceResource);
public:
	static ID3D11Device* GetDevice() { return device; }
	static ID3D11DeviceContext* GetContext() { return context; }

	template<typename TShader>
	static HRESULT LoadShader(std::wstring fileName, OUT TShader** shader) {
		return S_FALSE;
	}
	template<> static HRESULT LoadShader<ID3D11VertexShader>(std::wstring fileName, OUT ID3D11VertexShader** shader)
	{
		auto shaderBlob = DX::ReadData(fileName.c_str());
		map_shaderBlob[fileName] = shaderBlob;

		DX::ThrowIfFailed(
			device->CreateVertexShader(
				shaderBlob.data(),
				shaderBlob.size(),
				nullptr,
				shader)
		);
		return S_OK;
	}
	template<> static HRESULT LoadShader<ID3D11PixelShader>(std::wstring fileName, OUT ID3D11PixelShader** shader)
	{
		auto shaderBlob = DX::ReadData(fileName.c_str());
		map_shaderBlob[fileName] = shaderBlob;

		DX::ThrowIfFailed(
			device->CreatePixelShader(
				shaderBlob.data(),
				shaderBlob.size(),
				nullptr,
				shader)
		);
		return S_OK;
	}
	static std::vector<uint8_t> GetShaderBlob(std::string fileName);
	static std::vector<uint8_t> GetShaderBlob(std::wstring fileName);
private:
	static ID3D11Device * device;
	static ID3D11DeviceContext * context;
	static std::map<std::wstring, std::vector<uint8_t>> map_shaderBlob;
};
