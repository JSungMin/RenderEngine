#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "MonoObject.h"
#include "pch.h"
using namespace std;

class GameObject : public MonoObject {
public:
	GameObject Instantiate() {}

	template<typename T>
	T AddComponent(T);
	void SetParent(GameObject &object_) {}
	void AddChild(GameObject &object_) {}
	
private:
	vector<MonoObject*> ComponentCollection;
};