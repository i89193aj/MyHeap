#pragma once
// 定義宏區區分 DLL 的導入與導出
#define BUILDING_DLL

#ifdef BUILDING_DLL
#define DLL_API __declspec(dllexport)  // 導出符號
#else
#define DLL_API __declspec(dllimport)  // 導入符號
#endif

#include <string>
#include <iostream>
#include <vector>       // 若成員變數用到 std::vector
#include <map>          // 若有 std::map 變數
#include <unordered_map>// 若有 std::unordered_map 變數



// 節點類定義
template<typename T>
class DLL_API Node {
public:
    T val;
    Node<T>* next;
    Node<T>* random;

    Node(T val) : val(val), next(nullptr), random(nullptr) {}
    Node(T val, Node<T>* next) : val(val), next(next), random(nullptr) {}
    Node(T val, Node<T>* next, Node<T>* random) : val(val), next(next), random(random) {}

};

// MyHeap 類定義
template <typename T>
class DLL_API MyHeap {
private:
    
public:
    /*MyHeap();
    MyHeap(const MyHeap& _DataStructure);
    ~MyHeap();*/

    // ======= Leetcode Solutions =======
    void Leetcode_Sol_xxx(int& nums, int _solution);
    void DataStructure_xxx(int& nums);



    // ======= Leetcode Solutions =======
};

// 顯示實例化模板，以便在 DLL 中生成特定類型
extern template class DLL_API MyHeap<int>;
extern template class DLL_API MyHeap<std::string>;

#pragma region OOP
/*
class Base {
public:
    virtual void foo() = 0;  // 純虛擬函式
};

class Derived : public Base {
    // ❌ 沒有覆寫 foo()，所以仍然是抽象類別
};

class MoreDerived : public Derived {
public:
    void foo() override {  // ✅ MoreDerived 有覆寫 foo()
        std::cout << "MoreDerived foo()" << std::endl;
    }
};

如果你想建立該類的物件，子類就「一定要」覆寫純虛擬函式。
如果子類仍然是抽象類別，就不一定要覆寫純虛擬函式。
C++11 之後允許純虛擬函式 = 0 但仍提供函式體，可作為預設行為。
*/
#pragma endregion


