#include <iostream>
#include <string>
using namespace std;

// 抽象组件 - 数据源
class DataSource {
public:
    virtual ~DataSource() = default;
    virtual void writeData(const std::string& data) = 0;
    virtual std::string readData() = 0;
};

// 具体组件 - 标准输入数据源
class StdDataSource: public DataSource {
private:
    std::string data;
public:
    void writeData(const std::string& data) override {
        // TODO
        cout << data << '\n';
    }

    std::string readData() override {
        // TODO
        cin >> data;
        return data;
    }
};

// 装饰器基类
class DataSourceDecorator: public DataSource {
protected:
    DataSource* wrappee;
public:
    explicit DataSourceDecorator(DataSource* source) : wrappee(source) {}
    virtual ~DataSourceDecorator() { delete wrappee; }
};

// 具体装饰器 - 加密
class EncryptionDecorator: public DataSourceDecorator {
private:
    string data;
public:
    explicit EncryptionDecorator(DataSource* source): DataSourceDecorator(source) {}

    void writeData(const std::string& data) override {
        // TODO
        cout << "ENCRYPTED(" << data << ")\n";
        this->data = "ENCRYPTED(" + data + ")";
    }

    std::string readData() override {
        // TODO
        const string prefix = "ENCRYPTED(";
        const string suffix = ")";

        if (data.rfind(prefix, 0) == 0 && data.size() > prefix.size() + suffix.size()) {
            return data.substr(prefix.size(), data.size() - prefix.size() - suffix.size());
        }
        return data;
    }
};

// 具体装饰器 - 压缩
class CompressionDecorator: public DataSourceDecorator {
private:
    string data;
public:
    explicit CompressionDecorator(DataSource* source): DataSourceDecorator(source) {}

    void writeData(const std::string& data) override {
        // TODO
        cout << "COMPRESSED(" << data << ")\n";
        this->data = "COMPRESSED(" + data + ")";
    }

    std::string readData() override {
        // TODO
        const string prefix = "COMPRESSED(";
        const string suffix = ")";

        if (data.rfind(prefix, 0) == 0 && data.size() > prefix.size() + suffix.size()) {
            return data.substr(prefix.size(), data.size() - prefix.size() - suffix.size());
        }
        return data;
    }
};