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
#define  VT_BOOL 132 
#define  VT_I1 131 
#define  VT_I2 130 
#define  VT_UI1 129 
#define  VT_UI2 128 

__attribute__((used)) static unsigned int get_ulong_val(unsigned int val, int vt)
{
    switch(vt) {
    case VT_I2:
    case VT_BOOL:
    case VT_UI2:
        return val & 0xffff;
    case VT_I1:
    case VT_UI1:
        return val & 0xff;
    }

    return val;
}