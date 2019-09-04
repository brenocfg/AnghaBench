#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int xmlLineNumbersDefaultValue; } ;

/* Variables and functions */
 scalar_t__ IS_MAIN_THREAD ; 
 TYPE_1__* xmlGetGlobalState () ; 
 int xmlLineNumbersDefaultValue ; 

int *
__xmlLineNumbersDefaultValue(void) {
    if (IS_MAIN_THREAD)
	return (&xmlLineNumbersDefaultValue);
    else
	return (&xmlGetGlobalState()->xmlLineNumbersDefaultValue);
}