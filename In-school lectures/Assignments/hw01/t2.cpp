#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Student
{
    int id;
    string name;
    int age;
    char gender;
    string birthPlace;
};

int rulesCount, currentSortRules[6];

// TODO: 完成比较函数 globalCompare

bool globalCompare(const Student &a, const Student &b)
{
    for (int i = 0; i < rulesCount; i++)
    {
        int rule = currentSortRules[i];
        int field = abs(rule);
        bool positive = (rule > 0);

        bool result = false;
        bool equal = false;

        switch (field)
        {
        case 1: // 学号
            result = (a.id < b.id);
            equal = (a.id == b.id);
            break;
        case 2: // 姓名
            result = (a.name < b.name);
            equal = (a.name == b.name);
            break;
        case 3: // 年龄
            result = (a.age < b.age);
            equal = (a.age == b.age);
            break;
        case 4: // 性别
            result = (a.gender < b.gender);
            equal = (a.gender == b.gender);
            break;
        case 5: // 出生地
            result = (a.birthPlace < b.birthPlace);
            equal = (a.birthPlace == b.birthPlace);
            break;
        }

        if (!equal)
        {
            return positive ? result : !result;
        }
    }

    return a.id < b.id;
}

// TODO: 完成排序函数 sortStudents

void sortStudents(Student students[], int n, bool (*compare)(const Student &a, const Student &b))
{
    sort(students, students + n, compare);
}

int main()
{
    int n, m;

    cin >> n >> m;
    Student students[50];
    for (int i = 0; i < n; i++)
    {
        cin >> students[i].id >> students[i].name >> students[i].age >> students[i].gender >> students[i].birthPlace;
    }

    while (m--)
    {
        cin >> rulesCount;
        for (int i = 0; i < rulesCount; i++)
        {
            cin >> currentSortRules[i];
        }

        sortStudents(students, n, globalCompare);

        // 输出排序后的结果
        for (int i = 0; i < n; i++)
        {
            cout << students[i].id << endl;
        }
    }

    return 0;
}