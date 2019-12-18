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
typedef  int /*<<< orphan*/  cmsInt32Number ;

/* Variables and functions */
 int /*<<< orphan*/  CheckGammaFloatTable (double) ; 

__attribute__((used)) static cmsInt32Number CheckGamma18Table(void)
{
    return CheckGammaFloatTable(1.8);
}