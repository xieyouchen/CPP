#include <iostream>
#include <concepts>

// 自定义 concept：要求 T 必须能用 < 比较
template <typename T>
concept LessComparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
};

template <LessComparable T>
T minValue(T a, T b) {
    return (a < b) ? a : b;
}

int main() {
    std::cout << minValue(3, 7) << "\n";   // ✅ int 满足
    std::cout << minValue(2.5, 1.2) << "\n"; // ✅ double 满足
    // struct X {}; minValue(X{}, X{});  // ❌ 报错，X 不可比较
}
