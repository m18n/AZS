#pragma once
#ifdef _WIN32
#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif
#else
#define CORE_API
#endif
#include<iostream>
extern "C"{
CORE_API bool CheckPassword(std::string password);
};