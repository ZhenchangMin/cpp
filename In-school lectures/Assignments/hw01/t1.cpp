// Summarize:
// 1.switch-case要写break
// 2.type要更新
// 3.可以直接返回{x, y}作为Point


#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// cmath 库就是 C 语言中的 math.h 库，提供了常用的数学函数（sqrt, pow, abs 等）和常量（M_PI 等）
const double PI = M_PI; // M_PI 是 cmath 库中定义的常量
enum Shape
{
    LINE = 1,
    RECTANGLE = 2,
    CIRCLE = 3
};
enum Query
{
    PERIMETER = 1,
    DISTANCE = 2
};

struct Point
{
    double x, y;
};
struct Geo
{
    // TODO: 定义图形
    Shape type;
    Point point1, point2;
    double r;
};

Point getCenter(const Geo &geo)
{
    switch (geo.type)
    {
    case LINE:
    {
        // TODO: 计算并返回线段中点
        return {(geo.point1.x + geo.point2.x) / 2, (geo.point1.y + geo.point2.y) / 2};
    }
    case RECTANGLE:
    {
        // TODO: 计算并返回矩形中心
        return {(geo.point1.x + geo.point2.x) / 2, (geo.point1.y + geo.point2.y) / 2};
    }
    case CIRCLE:
    {
        // TODO: 直接返回圆心
        return geo.point1;
    }
    default:
        break;
    }
    return {0, 0};
}

double calculatePerimeter(const Geo &geo)
{
    switch (geo.type)
    {
    case LINE:
    {
        // TODO: 计算并返回线段长度
        return sqrt(pow(geo.point1.x - geo.point2.x, 2) + pow(geo.point1.y - geo.point2.y, 2));
        break;
    }
    case RECTANGLE:
    {
        // TODO: 计算并返回矩形周长
        return 2 * (abs(geo.point1.x - geo.point2.x) + abs(geo.point1.y - geo.point2.y));
        break;
    }
    case CIRCLE:
    {
        // TODO: 计算并返回圆周长
        return 2 * PI * geo.r;
        break;
    }
    }
    return 0.0;
}

double calculateDistance(const Geo &geo1, const Geo &geo2)
{
    Point c1 = getCenter(geo1), c2 = getCenter(geo2);
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

int main()
{
    int n, m;
    Geo shapes[1000];

    // TODO: 参考输出部分，完成输入
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int geoType;
        cin >> geoType;

        switch (geoType)
        {
        case 1:
        {
            double x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            shapes[i].point1 = {x1, y1};
            shapes[i].point2 = {x2, y2};
            shapes[i].type = LINE;
            break;
        }

        case 2:
        {
            double x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            shapes[i].point1 = {x1, y1};
            shapes[i].point2 = {x2, y2};
            shapes[i].type = RECTANGLE;
            break;
        }

        case 3:
        {
            double x1, y1;
            cin >> x1 >> y1;
            shapes[i].point1 = {x1, y1};
            double r;
            cin >> r;
            shapes[i].r = r;
            shapes[i].type = CIRCLE;
            break;
        }
        }
    }

    // 四舍五入保留两位小数的输出
    cout << fixed << setprecision(2);
    for (int i = 0; i < m; i++)
    {
        int queryType;
        cin >> queryType;

        switch (queryType)
        {
        case PERIMETER:
        {
            int idx;
            cin >> idx;
            cout << calculatePerimeter(shapes[idx - 1]) << endl;
            break;
        }
        case DISTANCE:
        {
            int idx1, idx2;
            cin >> idx1 >> idx2;
            cout << calculateDistance(shapes[idx1 - 1], shapes[idx2 - 1]) << endl;
            break;
        }
        default:
            break;
        }
    }

    return 0;
}