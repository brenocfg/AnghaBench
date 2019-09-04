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
 int FSE_optimalTableLog_internal (unsigned int,size_t,unsigned int,int) ; 

unsigned HUF_optimalTableLog(unsigned maxTableLog, size_t srcSize, unsigned maxSymbolValue)
{
	return FSE_optimalTableLog_internal(maxTableLog, srcSize, maxSymbolValue, 1);
}