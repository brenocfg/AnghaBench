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
typedef  unsigned long UINT32 ;

/* Variables and functions */

__attribute__((used)) static unsigned long dwarf2_get_u4(const unsigned char* ptr)
{
    return *(const UINT32*)ptr;
}