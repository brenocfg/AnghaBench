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
 size_t FSE_NCOUNTBOUND ; 

size_t FSE_NCountWriteBound(unsigned maxSymbolValue, unsigned tableLog)
{
	size_t const maxHeaderSize = (((maxSymbolValue + 1) * tableLog) >> 3) + 3;
	return maxSymbolValue ? maxHeaderSize : FSE_NCOUNTBOUND; /* maxSymbolValue==0 ? use default */
}