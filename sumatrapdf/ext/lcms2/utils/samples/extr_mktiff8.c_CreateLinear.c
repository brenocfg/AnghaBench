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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;

/* Variables and functions */
 int /*<<< orphan*/ * cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static
cmsToneCurve* CreateLinear(void)
{
	cmsUInt16Number Linear[2] = { 0, 0xffff };

	return cmsBuildTabulatedToneCurve16(0, 2, Linear);          
}