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

__attribute__((used)) static unsigned readInt(const char** argument)
{
    unsigned val = 0;
    while ((**argument>='0') && (**argument<='9')) {
        val *= 10;
        val += **argument - '0';
        (*argument)++;
    }
    return val;
}