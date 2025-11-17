
#include <iostream>
#include <sstream>
using namespace std;

class BaseCalculator {
protected:
public:
    ostringstream oss;
    virtual void calculate(double, double){}
    friend ostream &operator<<(ostream &, const BaseCalculator*);
};

// 加法计算器类
class AddCalculator : public BaseCalculator {
    void calculate(double, double);
};

// 减法计算器类
class SubCalculator : public BaseCalculator {
    void calculate(double, double);
};

