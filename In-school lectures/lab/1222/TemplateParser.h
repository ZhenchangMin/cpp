// 此头文件不需要修改，请在 TemplateParser.cpp 中实现相应逻辑

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// 类型结构体
struct Type {
    std::string name;
    
    bool operator==(const Type &other) const {
        return name == other.name;
    }
    bool operator!=(const Type &other) const {
        return !(*this == other);
    }
    bool operator>(const Type &other) const {
        return name > other.name;
    }
    bool operator<(const Type &other) const {
        return name < other.name;
    }
    
    // 判断是否为模板参数（规则：长度为1且为大写字母）
    bool is_template_param() const {
        return name.size() == 1 && std::isupper(name[0]);
    }
};

// 函数或模板函数定义
struct TemplateFunction {
    std::string name;
    std::vector<Type> parameters; // 形参列表
    bool is_template;             // 是否为模板函数
};

// 调用点信息
struct CallSite {
    std::string function_name;
    std::vector<Type> arguments; // 实参列表
};

// 核心解析函数
std::string resolve_call(const std::vector<TemplateFunction> &functions, CallSite cs);