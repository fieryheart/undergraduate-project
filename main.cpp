/*
 * @Description: 程序main函数
 * @Author: fieryheart
 * @LastEditors: Please set LastEditors
 * @Date: 2019-04-03 21:07:46
 * @LastEditTime: 2019-04-04 22:39:30
 */
#include <iostream>
#include <cstdlib>
#include "./Utils.h"

using namespace std;

int main()
{
    int seed = 100;
    cout << "random number: " << getRandomNumber(seed) << endl;
    return 0;
}