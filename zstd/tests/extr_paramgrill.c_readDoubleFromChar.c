#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static double readDoubleFromChar(const char** stringPtr)
{
    double result = 0, divide = 10;
    while ((**stringPtr >='0') && (**stringPtr <='9')) {
        result *= 10, result += **stringPtr - '0', (*stringPtr)++ ;
    }
    if(**stringPtr!='.') {
        return result;
    }
    (*stringPtr)++;
    while ((**stringPtr >='0') && (**stringPtr <='9')) {
        result += (double)(**stringPtr - '0') / divide, divide *= 10, (*stringPtr)++ ;
    }
    return result;
}