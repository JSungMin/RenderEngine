#include "pch.h"
#pragma once

class Texture
{
public :
	/*	Sampler Util Method Block
	*	Sampler를 제작 혹은 수정하는데 사용되는 Method 정의	
	*/
	static Microsoft::WRL::ComPtr<ID3D11SamplerState>	CreateDefaultSampler();
	void UpdateSampler(
		D3D11_FILTER filter,
		D3D11_TEXTURE_ADDRESS_MODE u,
		D3D11_TEXTURE_ADDRESS_MODE v,
		D3D11_TEXTURE_ADDRESS_MODE w);

	/*	ID3D11Texture2D, 3D Util Method Block
	*	Texture2D, 3D 객체를 생산하는데 사용되며, 
	*	생산된 Texture2D, 3D는 This 객체의 Resource를 통해 참조된다.
	*	2D와 3D 구분은 파라미터에 depth에 관한 내용이 있는지를 통해 구분된다.
	*	CreateFromFile은 ResourceManager의 LoadWICTexture 함수를 Extend 시킨 함수다.
	*/
	static Microsoft::WRL::ComPtr<ID3D11Texture2D>		CreateDefaultTexture(int width, int height, DXGI_FORMAT format, D3D11_BIND_FLAG bind);
	static Microsoft::WRL::ComPtr<ID3D11Texture3D>		CreateDefaultTexture(int widht, int height, int depth, DXGI_FORMAT format, D3D11_BIND_FLAG bind);

	static Microsoft::WRL::ComPtr<ID3D11Texture2D>		CreateDynamicTexture(int width, int height, DXGI_FORMAT format, D3D11_BIND_FLAG bind);
	static Microsoft::WRL::ComPtr<ID3D11Texture3D>		CreateDynamicTexture(int width, int height, int depth, DXGI_FORMAT format, D3D11_BIND_FLAG bind);
	
	static Texture*										CreateTextureFromFile(std::wstring fileName);


private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			sampler;
	Microsoft::WRL::ComPtr<ID3D11Resource>				texture;			//	Can Downcasting to ID3D11Texture2D or ID3D11Texture3D
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	textureSRV;
};