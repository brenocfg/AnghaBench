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
typedef  double cmsFloat32Number ;

/* Variables and functions */

__attribute__((used)) static cmsFloat32Number StraightLine( cmsFloat32Number x)
{
    return (cmsFloat32Number) (0.1 + 0.9 * x);
}