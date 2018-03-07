#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "pch.h"
using namespace std;

class Transform;

class MonoObject {
public:
	// Properties
	MonoObject* gameObject;
	unsigned long long fileID;
	string name;
	string tag;
	int layer;
	bool isActived;
	MonoObject* parent;
	vector<MonoObject*> children;
	Transform *transform;
	
	// Methods
	MonoObject();
	~MonoObject();
	
	template<typename T>
	T GetComponent() {}
	virtual void Update() {}
	virtual void Destroy() {}
};