#include "inventory.h"
#include <iostream>
using namespace std;

void Inventory::add(Thing thing)
{
    for (int i = 0; i < size; i++)// 注意不使用:things,因为things已经初始化，访问size以外的会导致未定义行为，这一点很重要！
    {
        if (things[i].getCategory() == thing.getCategory() && things[i].getQuality() == thing.getQuality())
        {
            things[i].setStorage(things[i].getStorage() + thing.getStorage());
            return;//找到了，直接返回
        }
    }
    // 如果不存在，添加新物品，但检查数组是否已满
    if (size < 80)
    {
        things[size] = thing;
        size++;
    }
}

void Inventory::inquiry(int category)
{
    int counts[4] = {0, 0, 0, 0}; // 初始化四个品质的数量为0，用数组记录每个品质的数量，简洁高效
    for (int i = 0; i < size; i++)
    {
        if (things[i].getCategory() == category)
        {
            int q = things[i].getQuality();
            if (q >= 0 && q < 4)
            {
                counts[q] += things[i].getStorage();
            }
        }
    }
    cout << counts[0] << ' ' << counts[1] << ' ' << counts[2] << ' ' << counts[3] << endl;
}
void Inventory::combine(int category, int a, int b, int c, int d)//这个功能的实现是最复杂的
{
    //get storages of each quality
    int counts[4] = {0, 0, 0, 0};
    for (int i = 0; i < size; i++)
    {
        if (things[i].getCategory() == category)
        {
            int q = things[i].getQuality();
            if (q >= 0 && q < 4)
            {
                counts[q] += things[i].getStorage();
            }
        }
    }

    // 计算各品质的需求和消耗
    int required[4] = {a, b, c, d};
    int consumed[4] = {0, 0, 0, 0};

    // 从最高品质开始处理（橙色），再依次往下
    for (int quality = 3; quality >= 0; quality--)
    {
        // 先使用当前品质的库存
        int available = counts[quality];
        int need = required[quality];

        // 计算需要消耗的当前品质数量
        int use_from_stock = (available < need) ? available : need;//如果够用就用need个数，否则全部用掉
        consumed[quality] = use_from_stock;

        // 计算不足的部分需要通过合成获得
        int deficit = need - use_from_stock;

        // 如果需要合成，且不是最低品质
        if (deficit > 0 && quality > 0)
        {
            // 计算需要多少低品质物品来合成
            int needed_from_lower = deficit * 3;//每个合成需要3个低品质物品，并且我们有deficit的缺口

            // 将这部分需求加到低品质的需求上
            required[quality - 1] += needed_from_lower;
        }
        else if (deficit > 0 && quality == 0)
        {
            // 最低品质不足，无法满足需求
            cout << "-1 -1 -1 -1" << endl;
            return;
        }
    }

    // 输出消耗的各品质数量
    cout << consumed[0] << " " << consumed[1] << " " << consumed[2] << " " << consumed[3] << endl;
}

void Inventory::use(int *numbers)
{
    int category = numbers[0];
    int reduce[4] = {numbers[1], numbers[2], numbers[3], numbers[4]};

    // 遍历所有物品，找到指定类别的所有品质
    for (int i = 0; i < size; i++)
    {
        if (things[i].getCategory() == category)
        {
            int quality = things[i].getQuality();
            if (quality >= 0 && quality < 4 && reduce[quality] > 0)
            {
                things[i].setStorage(things[i].getStorage() - reduce[quality]);
                reduce[quality] = 0; // 标记该品质已处理
            }
        }
    }
}