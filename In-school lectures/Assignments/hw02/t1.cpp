#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Student {
private:
    static int totalStudents;  // 静态成员：总学生数
    static double totalScore;  // 静态成员：总成绩
    int id;                    // 学号
    string name;               // 姓名
    double score;              // 成绩
    
public:
    // TODO: 完成构造函数，初始化学生信息并更新静态成员
    Student(int id, string name, double score){
        this -> id = id;
        this -> name = name;
        this -> score = score;
        this -> totalStudents ++;
        this -> totalScore += score;
    }
    
    // TODO: 完成析构函数，在对象销毁时更新静态成员
    ~Student(){
        this -> totalStudents --;
        this -> totalScore -= score;
    }
    
    // TODO: 实现获取平均成绩的静态成员函数
    static double getAverageScore(){
        if (totalStudents == 0) {
            return 0;
        }
        return totalScore / totalStudents;
    }
    
    // TODO: 实现获取总学生数的静态成员函数
    static int getTotalStudents(){
        return totalStudents;
    }
};

// TODO: 初始化静态成员变量
int Student::totalStudents = 0;
double Student::totalScore = 0;


// main函数部分请勿修改
int main() {
    int n, m;
    cin >> n; 
    
    vector<Student*> students; 

    for (int i = 0; i < n; i++) {
        int id;
        string name;
        double score;
        cin >> id >> name >> score;
        students.push_back(new Student(id, name, score));
    }
    
    cout << Student::getTotalStudents() << " ";
    cout << fixed << setprecision(2) << Student::getAverageScore() << endl;
    
    cin >> m; 
    
    for (int i = 0; i < m; i++) {
        delete students[i];
    }
    
    cout << Student::getTotalStudents() << " ";
    cout << fixed << setprecision(2) << Student::getAverageScore() << endl;
    
    for (int i = m; i < n; i++) {
        delete students[i];
    }
    
    return 0;
}