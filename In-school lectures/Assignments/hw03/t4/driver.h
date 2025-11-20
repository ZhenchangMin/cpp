// TODO: 完成 Device 类的定义
#include <string>
#include <iostream>
using namespace std;
class Device {
protected:
    string deviceId;
public:
    Device(const string& id) : deviceId(id) {}
    virtual void allocate(){
        cout << "Allocate device " << deviceId << endl;
    }
    string getInfo(){
        return "Device ID: " + deviceId;
    }
};

// TODO: 完成 InputDevice 类的定义
class InputDevice: public virtual Device {
protected:
    int inputSpeed;
    int scanQuality;
public:
    InputDevice(const string& id, int speed, int quality)
        : Device(id), inputSpeed(speed), scanQuality(quality) {}
    void allocate() override {
        cout << "Allocate input device " << deviceId << ", speed: " << inputSpeed
             << " ppm, quality: " << scanQuality << " DPI" << endl;
    }
    void previewScan(){
        cout << "Input device " << deviceId << " starting preview scan, quality: " << scanQuality << " DPI" << endl;
    }
};

// TODO: 完成 OutputDevice 类的定义
class OutputDevice : public virtual Device{
protected:
    int outputResolution;
    int printSpeed;
public:
    OutputDevice(const string& id, int resolution, int speed)
        : Device(id), outputResolution(resolution), printSpeed(speed) {}
    void allocate() override {
        cout << "Allocate output device " << deviceId << ", resolution: " << outputResolution 
        << " DPI, speed: " << printSpeed << " ppm" << endl;
    }
    void calibrate(){
        cout << "Calibrating output device "<< deviceId << ", target resolution: "<< outputResolution << " DPI" << endl;
    }
};

// TODO: 完成 MultiFunctionDevice 类的定义
class MultiFunctionDevice : public InputDevice, public OutputDevice {
protected:
    bool colorSupport;
public:
    MultiFunctionDevice(const string& id, int inSpeed, int inQuality, int outRes, int outSpeed, bool color)
        : Device(id), InputDevice(id, inSpeed, inQuality), OutputDevice(id, outRes, outSpeed), colorSupport(color) {}
    void allocate() override {
        InputDevice::allocate();
        OutputDevice::allocate();
        cout << "Enable multi-function device " << deviceId << ", color support: " 
             << colorSupport << endl;
    }
    void copyDocument(int pages){
        InputDevice::previewScan();
        cout << "Copying " << pages << " pages document" << endl;
    }
};
