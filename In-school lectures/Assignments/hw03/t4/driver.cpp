#include <iostream>
#include <string>
#include "driver.h"
using namespace std;

// TODO: 完成各个类成员函数的实现

// TIPS: 提交时请确保不要包含 main 函数！
int main() {
    // 测试纯输入设备
    cout << "=== Testing Input Device ===" << endl;
    InputDevice scanner("SCN-001", 20, 300);
    scanner.allocate();
    scanner.previewScan();
    
    // 测试纯输出设备
    cout << "=== Testing Output Device ===" << endl;
    OutputDevice printer("PRN-001", 600, 15);
    printer.allocate();
    printer.calibrate();
    
    // 测试多功能设备
    cout << "=== Testing Multi-Function Device ===" << endl;
    MultiFunctionDevice mfd("MFD-001", 25, 400, 600, 18, true);
    mfd.allocate();
    mfd.previewScan();    // 继承自输入设备
    mfd.calibrate();      // 继承自输出设备  
    mfd.copyDocument(5);  // 自身功能
    
    // 测试多态性
    cout << "=== Testing Polymorphism ===" << endl;
    Device* device = &mfd;
    device->allocate();
    
    return 0;
}