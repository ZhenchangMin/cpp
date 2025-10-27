#include <iostream>
#include <iomanip>
using namespace std;

class SensorBuffer {
protected:
    double* data;
    size_t size;
    int times = 0;

public:
    // TODO: 完成构造函数
    SensorBuffer(size_t n = 0){
        this->data = (double *)malloc(n * sizeof(double));
        size = n;
        cout << "[SensorBuffer] Constructed, size=" << n << '\n';
    }
    SensorBuffer(size_t n, double* data){
        size = n;
        this->data = (double *)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++){
            this->data[i] = data[i];
        }
        cout << "[SensorBuffer] Constructed, size=" << n << '\n';
    }

    SensorBuffer(const SensorBuffer& other){
        size = other.size;
        data = (double *)malloc(size);
        for (int i = 0; i < size; i++){
            this->data[i] = other.data[i];
        }
        cout << "[SensorBuffer] Copied (deep copy)" << '\n';
    }

    // TODO: 完成析构函数
    virtual ~SensorBuffer(){
        size = 0;
        times++;
        if (times > 1){
            cout << "[SensorBuffer] Already released" << '\n';
        }
        else cout << "[SensorBuffer] Data released" << '\n';
        if (data != nullptr){
            data = nullptr;
        }
    }

    // TODO: 完成成员函数
    double get(int id) const{
        return data[id];
    }
    void set(int id, double value){
        data[id] = value;
    }
    virtual double average() const{
        double total = 0;
        for(int i = 0; i < size; i++){
            total += data[i];
        }
        return total / size;
    }
    virtual void printInfo() const{
        cout << "[SensorBuffer] Info: size=" << size << '\n';
    }
};

class TemperatureBuffer : public SensorBuffer {
private:
    string unit;

public:
    // TODO: 完成构造函数
    TemperatureBuffer(size_t n, const string& unit = "C"):SensorBuffer(n){
        this->unit = unit;
        cout << "[TemperatureBuffer] Constructed, unit=" << unit << '\n';
    }
    TemperatureBuffer(size_t n, double* init_data, const string& unit = "C"):SensorBuffer(n, init_data){
        this->unit = unit;
        cout << "[TemperatureBuffer] Constructed, unit=" << unit << '\n';
    }

    TemperatureBuffer(const TemperatureBuffer& other):SensorBuffer(other){
        unit = other.unit;
        size = other.size;
        data = (double *)malloc(size);
        for (int i = 0; i < size; i++){
            this->data[i] = other.data[i];
        }
        cout << "[TemperatureBuffer] Copied from another TemperatureBuffer" << '\n';
    }

    // TODO：完成析构函数
    virtual ~TemperatureBuffer(){
        size = 0;
        if (data != nullptr) data = nullptr;
        cout << "[TemperatureBuffer] Destructor called" << '\n';
    }

    // TODO: 完成成员函数
    double average() const{
        double total = 0;
        for(int i = 0; i < size; i++){
            total += data[i];
        }
        return total / size;
    }
    void printInfo() const{
        cout << "[TemperatureBuffer] Info: unit=" << unit << ", size=" << size << '\n';
    }
};