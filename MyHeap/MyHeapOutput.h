#pragma once
#define BUILDING_DLL
#ifdef BUILDING_DLL
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
extern "C" {
    /*這裡是當Output那裡包完func後，可以用這個方式建立dll給外部用!(詳情可以看MyLinklist，那裡有實際包一次給c#用)*/
}

