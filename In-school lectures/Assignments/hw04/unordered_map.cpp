#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class DataClass {
private:
  std::vector<std::string> data_;

public:
  DataClass(const std::vector<std::string> &data) : data_(data) {}

  std::string HashKey() const {
    // Your code here
    std::string key;
    for (string s : data_) {
      key += s;
    }
    return key;
  }

  bool operator==(const DataClass &dc) const {
    // Your code here
    auto &other_data = dc.data_;
    for (string s : data_) {
      auto it = std::find(other_data.begin(), other_data.end(), s);
      if (it == other_data.end()) {
        return false;
      }
    }
    return true;
  }
};





//*******************************************************************************
//
//                               下面的内容不需要修改
//
//*******************************************************************************

struct DataClassHash {
  size_t operator()(const DataClass &dc) const {

    std::string str = dc.HashKey();

    return std::hash<std::string>()(str);
  }
};

void testInternal(const std::vector<std::vector<std::string>> input){
  std::vector<DataClass> data_classes;
  std::unordered_map<DataClass, int, DataClassHash> data_map;
  
  for(auto& params: input){
    data_classes.emplace_back(DataClass(params));
  }
  
  for(auto& data_class: data_classes){
    data_map[data_class]++;
  }

  for(auto& data_class: data_classes){
    std::cout << data_map[data_class] << std::endl;
  }
}

std::vector<std::string> parseLine(const std::string& line) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string item;
    
    while (std::getline(ss, item, ' ')) {
        if (!item.empty()) {
            result.push_back(item);
        }
    }
    
    return result;
}

int main() {
    int n;
    cin >> n;
    cin.ignore(); 
    std::vector<std::vector<std::string>> inputs;
    
    for (int i = 0; i < n; i++) {
        std::string line;
        std::getline(cin, line);
        
        auto params = parseLine(line);
        inputs.push_back(params);
    }
    testInternal(inputs);
    
    return 0;
}