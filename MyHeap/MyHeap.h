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
#include <algorithm>

#include <stdexcept>    // throw error message
#include <functional>  // ✅ 如果你使用 std::less 或 std::greater



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
template <typename T,typename Container = std::vector<T>,typename Compare = std::less<T>>
class DLL_API MyHeap {
private:
    Container heap;
    Compare cmp;
    
    /*若某個節點是 index i：左子節點：2*idx + 1、右子節點：2*i + 2、父節點：(i - 1) / 2*/
    /*int idx = heap.size() / 2 - 1 代表：整顆樹的中間的第一位父節點 -> 0()*/
    void heapify_up(int idx) {
        while (idx > 0) {   //如果idx = 0，代表現在在top()
            int parent = (idx - 1) / 2;
            if (!cmp(heap[parent], heap[idx])) break;//如果要跟priority 一樣那就必須加!(因為C++內部定義就是less<T>是由大到小)
            std::swap(heap[parent],heap[idx]);  
            idx = parent;
        }
    }

    void heapify_down(int idx) {
        int isize = heap.size();
        while (2 * idx + 1 < isize) { //會用左子節點的原因：因為如果左子節點沒有的話，那右子節點一定也沒有!
            int child = 2 * idx + 1;  //左子節點
            if (child + 1 < isize && cmp(heap[child], heap[child + 1])) //左、右子節點先比
                child++;
            if (cmp(heap[child], heap[idx])) break; //贏的跟當前父節點比
            std::swap(heap[child],heap[idx]);
            idx = child;
        }
    }

    // 遞迴 heapify（max-heap）
    void heapify_down_Recursion(int idx) {
        int isize = heap.size();
        int largest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < isize && heap[left] > heap[largest])
            largest = left;

        if (right < isize && heap[right] > heap[largest])
            largest = right;

        if (largest != idx) {
            std::swap(heap[idx], heap[largest]);
            heapify_down_Recursion(largest);
        }
    }

    template<typename T>
    struct MyLess {
        bool operator()(const T& a, const T& b) const {
            return a < b;
        }
    };

    template<typename T>
    struct MyGreater {
        bool operator()(const T& a, const T& b) const {
            return a > b;
        }
    };

    
        
public:
    MyHeap(Container cmp = Container(), Compare container = Compare(), int mthd = 1) :heap(std::move(cmp)), cmp(std::move(container)) {
        switch (mthd)
        {
        case 1:
            for (int i = heap.size() / 2 - 1; i >= 0; i--)
                heapify_down(i);
            break;
        case 2:
            for (int i = heap.size() / 2 - 1; i >= 0; i--)
                heapify_down_Recursion(i);
            break;

        default:
            for (int i = heap.size() / 2 - 1; i >= 0; i--)
                heapify_down(i);
            break;
        }
        /*  方式	優點	                缺點
            遞迴	寫法簡潔、易懂	        對 stack 較敏感（大資料可能 stack overflow）
            迴圈	更穩定、不怕堆疊太深	寫法略繁雜                                   */
    };


    void push(const T& val) {
        heap.push_back(val);
        heapify_up(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) throw std::out_of_range("Heap is empty.");
        std::swap(heap.front(), heap.back());
        heap.pop_back();
        heapify_down(0);
    }

    const T& top() const {
        if (heap.empty()) throw std::out_of_range("Heap is empty.");
        heap.front();
    }

    bool empty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }

    //~MyHeap();
    /*  你需不需要自己寫 ~MyHeap()？	                要看你的類別有沒有管理資源（如 new 或檔案等）
        只是 std::vector, std::function 等 STL 成員？	❌ 不需要寫，交給編譯器
        有 new, malloc, fopen, socket？	                ✅ 需要寫 destructor 負責釋放資源    */

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


