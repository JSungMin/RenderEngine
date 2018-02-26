#include "pch.h"
#include <map>
#pragma once

class ResourceManager
{
public:
	ResourceManager(ID3D11Device* device) 
	{
		Init(device);
	}
public:
	static void Init(ID3D11Device* device);
public:
	static HRESULT LoadVertexShader(std::wstring fileName, OUT ID3D11VertexShader** vertexShader);
	static HRESULT LoadPixelShader	(std::wstring fileName, OUT ID3D11PixelShader**	pixelShader);

	static std::vector<uint8_t> GetShaderBlob(std::string fileName);
	static std::vector<uint8_t> GetShaderBlob(std::wstring fileName);
private:
	static ID3D11Device * device;
	static std::map<std::wstring, std::vector<uint8_t>> map_shaderBlob;
};
