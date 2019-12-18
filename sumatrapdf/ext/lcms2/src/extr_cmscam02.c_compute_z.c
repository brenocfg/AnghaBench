#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cmsFloat64Number ;
struct TYPE_3__ {int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ cmsCIECAM02 ;

/* Variables and functions */
 scalar_t__ pow (int /*<<< orphan*/ ,double) ; 

__attribute__((used)) static
cmsFloat64Number compute_z(cmsCIECAM02* pMod)
{
    return (1.48 + pow(pMod -> n, 0.5));
}