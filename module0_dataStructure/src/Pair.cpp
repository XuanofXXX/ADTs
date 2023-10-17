/**
 * @brief Construct a new Pair object
 * @param T1 
 * @param T2 
 */

template<typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    // 默认构造函数
    Pair() {}

    // 带参数的构造函数
    Pair(const T1& a, const T2& b) : first(a), second(b) {}

    // 获取first成员的方法
    T1 first() const { return first; }

    // 获取second成员的方法
    T2 second() const { return second; }

    // 设置first成员的方法
    void setFirst(const T1& a) { first = a; }

    // 设置second成员的方法
    void setSecond(const T2& b) { second = b; }
};
