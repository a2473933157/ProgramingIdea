#pragma once
#ifndef __SMART_PTR_H
#define __SMART_PTR_H
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <regex>
#include <algorithm>

template<typename T>
class SmartPtr {
public:
	SmartPtr(std::initializer_list<T> items);
	SmartPtr(const SmartPtr& _copy);//Copy On Write
	SmartPtr(SmartPtr&& _rVal);
	SmartPtr& operator=(const SmartPtr& _copy);//Copy On Write
	SmartPtr& operator=(SmartPtr&& _rVal);
protected:
private:
	std::shared_ptr<std::vector<T>> _sharedPtr;
	std::unique_ptr<std::vector<T>> _uniquePtr;
};

template<typename T>
SmartPtr<T>::SmartPtr(std::initializer_list<T> items) {
	_sharedPtr = std::make_shared<T>(items);
	_uniquePtr(new std::vector<T>(items));
}

template<typename T>
SmartPtr<T>::SmartPtr(const SmartPtr& _copy) {
	_sharedPtr(_copy._sharedPtr);
	_uniquePtr(_copy._uniquePtr.release());
}

template<typename T>
SmartPtr<T>::SmartPtr(SmartPtr&& _rVal) {
	_sharedPtr(_rVal._sharedPtr);
	_uniquePtr(_rVal._uniquePtr.release());
}

template<typename T>
SmartPtr<T>&
SmartPtr<T>::operator=(const SmartPtr& _copy) {
	this->_sharedPtr.reset(_copy._sharedPtr);
	this->_uniquePtr.reset(_copy._uniquePtr.release());
	return *this;
}

template<typename T>
SmartPtr<T>&
SmartPtr<T>::operator=(SmartPtr&& _rVal) {
	this->_sharedPtr.reset(_rVal._sharedPtr);
	this->_uniquePtr.reset(_rVal._uniquePtr.release());
	return *this;
}

#endif
