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
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int OPJ_INT32 ;

/* Variables and functions */

OPJ_INT32 getValue(OPJ_UINT32 i)
{
    return ((OPJ_INT32)i % 511) - 256;
}