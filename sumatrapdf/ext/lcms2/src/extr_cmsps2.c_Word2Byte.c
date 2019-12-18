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
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  scalar_t__ cmsUInt16Number ;
typedef  double cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  floor (double) ; 

__attribute__((used)) static
cmsUInt8Number Word2Byte(cmsUInt16Number w)
{
    return (cmsUInt8Number) floor((cmsFloat64Number) w / 257.0 + 0.5);
}