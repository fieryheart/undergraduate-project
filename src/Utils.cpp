/*
 * @Author: fieryheart
 * @Description: tools
 * @Date: 2019-04-04 20:16:02
 * @LastEditTime: 2019-04-04 20:24:14
 */

#include "../Utils.h"

int getRandomNumber(unsigned int seed)
{
    srand(seed);
    return rand();
}