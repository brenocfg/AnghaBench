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
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL rop_uses_src(DWORD rop)
{
    return (((rop & 0xcc0000) >> 2) != (rop & 0x330000));
}