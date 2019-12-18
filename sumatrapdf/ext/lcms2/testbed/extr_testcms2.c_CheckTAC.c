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
typedef  int cmsInt32Number ;

/* Variables and functions */
 int /*<<< orphan*/  CheckOneTAC (int) ; 

__attribute__((used)) static
cmsInt32Number CheckTAC(void)
{
    if (!CheckOneTAC(180)) return 0;
    if (!CheckOneTAC(220)) return 0;
    if (!CheckOneTAC(286)) return 0;
    if (!CheckOneTAC(310)) return 0;
    if (!CheckOneTAC(330)) return 0;

    return 1;
}