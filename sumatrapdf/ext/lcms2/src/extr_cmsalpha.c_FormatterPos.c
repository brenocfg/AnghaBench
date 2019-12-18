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
typedef  int cmsUInt32Number ;

/* Variables and functions */
 int T_BYTES (int) ; 
 scalar_t__ T_ENDIAN16 (int) ; 
 scalar_t__ T_FLOAT (int) ; 

__attribute__((used)) static
int FormatterPos(cmsUInt32Number frm)
{
    cmsUInt32Number  b = T_BYTES(frm);

    if (b == 0 && T_FLOAT(frm))
        return 5; // DBL
#ifndef CMS_NO_HALF_SUPPORT
    if (b == 2 && T_FLOAT(frm))
        return 3; // HLF
#endif
    if (b == 4 && T_FLOAT(frm))
        return 4; // FLT
    if (b == 2 && !T_FLOAT(frm))
        return 1; // 16
    if (b == 1 && !T_FLOAT(frm))
        return 0; // 8
    if (b == 2 && T_ENDIAN16(frm))
        return 3;
    return -1; // not recognized
}