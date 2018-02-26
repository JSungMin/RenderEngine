#include "pch.h"
#pragma once

class Texture
{
public :
	/*	Sampler Util Method Block
	*	Sampler�� ���� Ȥ�� �����ϴµ� ���Ǵ� Method ����	
	*/
	static Microsoft::WRL::ComPtr<ID3D11SamplerState>	CreateDefaultSampler();
	void UpdateSampler(
		D3D11_FILTER filter,
		D3D11_TEXTURE_ADDRESS_MODE u,
		D3D11_TEXTURE_ADDRESS_MODE v,
		D3D11_TEXTURE_ADDRESS_MODE w);

	/*	ID3D11Texture2D, 3D Util Method Block
	*	Texture2D, 3D ��ü�� �����ϴµ� ���Ǹ�, 
	*	����� Texture2D, 3D�� This ��ü�� Resource�� ���� �����ȴ�.
	*	2D�� 3D ������ �Ķ���Ϳ� depth�� ���� ������ �ִ����� ���� ���еȴ�.
	*	CreateFromFile�� ResourceManager�� LoadWICTexture �Լ��� Extend ��Ų �Լ���.
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