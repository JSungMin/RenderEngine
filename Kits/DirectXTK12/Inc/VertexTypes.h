//--------------------------------------------------------------------------------------
// File: VertexTypes.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------

#pragma once

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3d12_x.h>
#else
#include <d3d12.h>
#endif

#include <DirectXMath.h>


namespace DirectX
{
    // Vertex struct holding position information.
    struct VertexPosition
    {
        VertexPosition() = default;

        VertexPosition(XMFLOAT3 const& position)
            : position(position)
        { }

        VertexPosition(FXMVECTOR position)
        {
            XMStoreFloat3(&this->position, position);
        }

        XMFLOAT3 position;
   
        static const D3D12_INPUT_LAYOUT_DESC InputLayout;

    private:
        static const int InputElementCount = 1;
        static const D3D12_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position and color information.
    struct VertexPositionColor
    {
        VertexPositionColor() = default;

        VertexPositionColor(XMFLOAT3 const& position, XMFLOAT4 const& color)
          : position(position),
            color(color)
        { }

        VertexPositionColor(FXMVECTOR position, FXMVECTOR color)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat4(&this->color, color);
        }

        XMFLOAT3 position;
        XMFLOAT4 color;

        static const D3D12_INPUT_LAYOUT_DESC InputLayout;

    private:
        static const int InputElementCount = 2;
        static const D3D12_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position and texture mapping information.
    struct VertexPositionTexture
    {
        VertexPositionTexture() = default;

        VertexPositionTexture(XMFLOAT3 const& position, XMFLOAT2 const& textureCoordinate)
          : position(position),
            textureCoordinate(textureCoordinate)
        { }

        VertexPositionTexture(FXMVECTOR position, FXMVECTOR textureCoordinate)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
        }

        XMFLOAT3 position;
        XMFLOAT2 textureCoordinate;

        static const D3D12_INPUT_LAYOUT_DESC InputLayout;

    private:
        static const int InputElementCount = 2;
        static const D3D12_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position and dual texture mapping information.
    struct VertexPositionDualTexture
    {
        VertexPositionDualTexture() = default;

        VertexPositionDualTexture(XMFLOAT3 const& position, XMFLOAT2 const& textureCoordinate0, XMFLOAT2 const& textureCoordinate1)
            : position(position),
            textureCoordinate0(textureCoordinate0),
            textureCoordinate1(textureCoordinate1)
        { }

        VertexPositionDualTexture(FXMVECTOR position,
            FXMVECTOR textureCoordinate0,
            FXMVECTOR textureCoordinate1)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat2(&this->textureCoordinate0, textureCoordinate0);
            XMStoreFloat2(&this->textureCoordinate1, textureCoordinate1);
        }

        XMFLOAT3 position;
        XMFLOAT2 textureCoordinate0;
        XMFLOAT2 textureCoordinate1;

        static const D3D12_INPUT_LAYOUT_DESC InputLayout;

    private:
        static const int InputElementCount = 3;
        static const D3D12_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position and normal vector.
    struct VertexPositionNormal
    {
        VertexPositionNormal() = default;

        VertexPositionNormal(XMFLOAT3 const& position, XMFLOAT3 const& normal)
          : position(position),
            normal(normal)
        { }

        VertexPositionNormal(FXMVECTOR position, FXMVECTOR normal)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat3(&this->normal, normal);
        }

        XMFLOAT3 position;
        XMFLOAT3 normal;
       
        static const D3D12_INPUT_LAYOUT_DESC InputLayout;

    private:
        static const int InputElementCount = 2;
        static const D3D12_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position, color, and texture mapping information.
    struct VertexPositionColorTexture
    {
        VertexPositionColorTexture() = default;

        VertexPositionColorTexture(XMFLOAT3 const& position, XMFLOAT4 const& color, XMFLOAT2 const& textureCoordinate)
          : position(position),
            color(color),
            textureCoordinate(textureCoordinate)
        { }

        VertexPositionColorTexture(FXMVECTOR position, FXMVECTOR color, FXMVECTOR textureCoordinate)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat4(&this->color, color);
            XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
        }

        XMFLOAT3 position;
        XMFLOAT4 color;
        XMFLOAT2 textureCoordinate;

        static const D3D12_INPUT_LAYOUT_DESC InputLayout;

    private:
        static const int InputElementCount = 3;
        static const D3D12_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position, normal vector, and color information.
    struct VertexPositionNormalColor
    {
        VertexPositionNormalColor() = default;

        VertexPositionNormalColor(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& color)
          : position(position),
            normal(normal),
            color(color)
        { }

        VertexPositionNormalColor(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR color)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat3(&this->normal, normal);
            XMStoreFloat4(&this->color, color);
        }

        XMFLOAT3 position;
        XMFLOAT3 normal;
        XMFLOAT4 color;

        static const D3D12_INPUT_LAYOUT_DESC InputLayout;

    private:
        static const int InputElementCount = 3;
        static const D3D12_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position, normal vector, and texture mapping information.
    struct VertexPositionNormalTexture
    {
        VertexPositionNormalTexture() = default;

        VertexPositionNormalTexture(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT2 const& textureCoordinate)
          : position(position),
            normal(normal),
            textureCoordinate(textureCoordinate)
        { }

        VertexPositionNormalTexture(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR textureCoordinate)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat3(&this->normal, normal);
            XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
        }

        XMFLOAT3 position;
        XMFLOAT3 normal;
        XMFLOAT2 textureCoordinate;

        static const D3D12_INPUT_LAYOUT_DESC InputLayout;

    private:
        static const int InputElementCount = 3;
        static const D3D12_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };


    // Vertex struct holding position, normal vector, color, and texture mapping information.
    struct VertexPositionNormalColorTexture
    {
        VertexPositionNormalColorTexture() = default;

        VertexPositionNormalColorTexture(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& color, XMFLOAT2 const& textureCoordinate)
          : position(position),
            normal(normal),
            color(color),
            textureCoordinate(textureCoordinate)
        { }

        VertexPositionNormalColorTexture(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR color, CXMVECTOR textureCoordinate)
        {
            XMStoreFloat3(&this->position, position);
            XMStoreFloat3(&this->normal, normal);
            XMStoreFloat4(&this->color, color);
            XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
        }

        XMFLOAT3 position;
        XMFLOAT3 normal;
        XMFLOAT4 color;
        XMFLOAT2 textureCoordinate;

        static const D3D12_INPUT_LAYOUT_DESC InputLayout;

    private:
        static const int InputElementCount = 4;
        static const D3D12_INPUT_ELEMENT_DESC InputElements[InputElementCount];
    };
}
