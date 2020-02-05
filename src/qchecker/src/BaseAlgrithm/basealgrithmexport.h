#pragma once

#ifdef BASE_ALGRITHM_EXPORT
#define BASE_ALGRITHM_API __declspec(dllexport)
#else
#define BASE_ALGRITHM_API __declspec(dllimport)
#endif