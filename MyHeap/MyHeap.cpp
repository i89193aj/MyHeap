/*Oscar Linkedlist*/
//#include "pch.h";
#include <iostream>
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()
#include <random>   // C++11 亂數庫
#include <vector>   // std::vector
#include <numeric>  // std::iota
#include"MyHeap.h"
#include <map>      //std::map
#include <unordered_map>  //std::unordered_map
using namespace std;

// 顯式實例化模板以便在 DLL 中包含特定類型
template class DLL_API MyHeap<int>;
template class DLL_API MyHeap<std::string>;

enum LeetcodeExam {
    Leetcodexxx,

    None,
};

#ifndef NOBUILDING_DLL  //#ifdef BUILDING_DLL
int main()
{
    #pragma region Leetcode program Test
    //try case
    LeetcodeExam ExamEnum = Leetcodexxx;    //ChangeForExam
    //intput
    vector<int> vInput1 = { 7,13,11,10,1 };
    vector<int> vInput2 = { 7,13,11,10,1 };
    vector<vector<int>> vvInput1 = { {1,2} ,{2,3},{3,4},{1,3} };
    string strinput1 = "bab";
    string strinput2 = "xaabacxcabaaxcabaax";
    int iInput1 = 0; int iInput2 = 0;
    //output
    int Ans = 0; vector<int> AnsVector; string AnsStr = ""; bool Ansbool = false;
    MyHeap<int>* Implementation = new MyHeap<int>();
    switch (ExamEnum)
    {
    case Leetcodexxx:
        //AnsVector = Implementation->Leetcode_Sol_21(vInput1, iInput1, 1);
        break;

    default:
        break;
    }
    #pragma endregion

    #pragma region random_device
    //srand(time(nullptr)); // 用目前時間作為隨機種子
    int randomNumber = rand() % 100 + 1; // 產生 1~100 之間的數字

    //比 rand() 更隨機，適合密碼學、模擬等需求。
    std::random_device rd;  // 取得隨機種子（硬體隨機數）
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 演算法
    std::uniform_int_distribution<int> dist(1, 100); // 產生範圍 1~100
    int randomNumber2 = dist(gen);
    #pragma endregion

    #pragma region vector
    std::vector<int>vec1(10);               // 建立 100 個元素未初始化
    std::vector<int> vec2(10, 0);           // 建立 100 個元素，每個都是 0
    std::vector<int> vec3(10);
    std::iota(vec3.begin(), vec3.end(), 0);  // 填入 0 到 99 (也可以)
    #pragma endregion

    #pragma region Map
    // 自訂比較函數（降序排列）
    struct Descending {
        bool operator()(int a, int b) const {
            return a > b; // 讓 key 由大到小排序
        }
    };
    std::map<int, std::string, Descending> m1;

    // 自訂相等函數
    struct MyEqual {
        bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
            return a.first == b.first && a.second == b.second; //first 是key，second是value
        }
    };

    // 自訂 hash 函數
    /* size_t：
    size_t 是 C/C++ 裡的一種 無符號整數類型，專門用來表示物件的大小或索引。它的具體大小取決於你的系統架構：
    32 位元系統：size_t 是 4 bytes（32 位元），範圍是 0 ~ 4,294,967,295
    64 位元系統：size_t 是 8 bytes（64 位元），範圍是 0 ~ 18,446,744,073,709,551,615
    📝 重點：
    無符號：保證為正數，因為負的大小沒有意義
    跨平台：根據編譯器與硬體架構自動調整大小
    */
    struct MyHash {
        std::size_t operator()(const std::pair<int, int>& p) const {
            return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);//^ 是 XOR（異或運算）
        }
    };

    /*
    ✅XOR (^)：用來混合 p.first 和 p.second 的哈希值，使得 unordered_map 的 key 分佈更均勻。
    ✅ << 1 左移：讓 p.second 的 bit pattern 變化，降低碰撞機率。
    ✅ 可能的進一步優化：可以用 * 31 等技巧來減少模式碰撞。
    ✅ 效果：這樣的設計可以讓 unordered_map<std::pair<int, int>> 減少哈希碰撞，提升存取速度。
    */
    struct PairHash {
        size_t operator()(const std::pair<int, int>& p) const {
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
        }
    };

    std::unordered_map<std::pair<int, int>, std::string, MyHash, MyEqual> umap;
    umap[std::make_pair(1, 2)] = "apple";
    umap[std::make_pair(3, 4)] = "banana";

    for (const auto& [key, value] : umap) {
        std::cout << "(" << key.first << ", " << key.second << "): " << value << '\n';
    }

    //Lambda 排序
    auto cmp = [](int a, int b) { return a > b; };
    std::map<int, std::string, decltype(cmp)> m(cmp);//decltype 精確獲取表達式的原始類型，不會調整型別。

    //插入(insert / operator[] / emplace)
    m.insert({ 4, "dog" });  // 插入 (不覆蓋)
    m[5] = "elephant";     // 插入 (會覆蓋舊值)
    m.emplace(6, "fox");   // 插入 (更高效)

    //查找(find / count)
    if (m.find(3) != m.end()) std::cout << "找到 key 3\n";
    if (m.count(3)) std::cout << "key 3 存在\n";

    //遍歷(for / iterator)
    for (const auto& [key, value] : m) { std::cout << key << ": " << value << '\n'; }
    for (auto it = m.begin(); it != m.end(); ++it) { std::cout << it->first << ": " << it->second << '\n'; }

    //刪除(erase)
    m.erase(2); // 刪除 key 為 2 的元素
    m.clear();  // 清空整個 map
    #pragma endregion

    #pragma region Set

    #pragma endregion

    #pragma region for
    //1.基本 for 迴圈 (經典寫法)
    for(int i = 0;i < vec1.size();i++)
        std::cout << vec1[i] << " ";  // 輸出每個元素
    //2.範圍 for 迴圈 (range-based for loop)
    for (int n : vec1) 
        std::cout << n << " ";        // 輸出每個元素
    //3.使用 auto 自動推導型別
    //只讀取並遍歷 (不修改)
    for (auto n : vec1) 
        std::cout << n << " ";        // 輸出每個元素

    //讀取並修改每個元素(使用 & 參考)
    for (auto& n : vec1) 
        std::cout << n << " ";        // 輸出每個元素

    //讀取並使用 const (避免修改)
    for (const auto& n : vec1) 
        std::cout << n << " ";        // 輸出每個元素
    //4.使用 auto 搭配迭代器(iterator)
    for (auto it = vec1.begin(); it != vec1.end(); ++it) { // ✅ 使用迭代器遍歷(auto = std::vector<int>::iterator)
        std::cout << *it << " ";
    }
    //上述等同此
    for (int* it = &vec1[0]; it != &vec1[vec1.size()-1]; ++it) {//vec12[vec12.size()] out of the range
        std::cout << *it << " ";
    }
#pragma endregion
}
#endif

#pragma endregion


#pragma region Leetcode xxx. Description
//Leetcode xxx. Description
template<typename T>
void MyHeap<T>::Leetcode_Sol_xxx(int& nums, int _solution) {
    switch (_solution)
    {
    case 1:
        return DataStructure_xxx(nums);
    default:
        return ; // 確保所有路徑都有回傳值
    }

    return ;
}

template<typename T>
void MyHeap<T>::DataStructure_xxx(int& nums) {
    return;
}
#pragma endregion

#pragma endregion















