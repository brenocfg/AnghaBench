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
typedef  int /*<<< orphan*/  luaL_Buffer ;
typedef  scalar_t__ UC ;

/* Variables and functions */
 scalar_t__* b64base ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static size_t b64encode(UC c, UC *input, size_t size, 
        luaL_Buffer *buffer)
{
    input[size++] = c;
    if (size == 3) {
        UC code[4];
        unsigned long value = 0;
        value += input[0]; value <<= 8;
        value += input[1]; value <<= 8;
        value += input[2]; 
        code[3] = b64base[value & 0x3f]; value >>= 6;
        code[2] = b64base[value & 0x3f]; value >>= 6;
        code[1] = b64base[value & 0x3f]; value >>= 6;
        code[0] = b64base[value];
        luaL_addlstring(buffer, (char *) code, 4);
        size = 0;
    }
    return size;
}