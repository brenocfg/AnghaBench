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
typedef  int /*<<< orphan*/  xmlStructuredErrorFunc ;
struct TYPE_2__ {int /*<<< orphan*/  xmlStructuredError; } ;

/* Variables and functions */
 scalar_t__ IS_MAIN_THREAD ; 
 TYPE_1__* xmlGetGlobalState () ; 
 int /*<<< orphan*/  xmlStructuredError ; 

xmlStructuredErrorFunc *
__xmlStructuredError(void) {
    if (IS_MAIN_THREAD)
	return (&xmlStructuredError);
    else
	return (&xmlGetGlobalState()->xmlStructuredError);
}