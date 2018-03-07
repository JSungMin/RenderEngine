#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "GameObject.h"
#include "pch.h"
using namespace std;

class Transform : MonoObject {
public:
	// Constructor and Destructor
	Transform(GameObject &gameObject_);
	~Transform();

	void Translate(DirectX::SimpleMath::Vector3 velocity);

	void SetParent(Transform &transform_);
	void AddChild(Transform &transform_);
	Transform GetChildAtIndex(int index);


private:
	DirectX::SimpleMath::Matrix mvp;
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
};