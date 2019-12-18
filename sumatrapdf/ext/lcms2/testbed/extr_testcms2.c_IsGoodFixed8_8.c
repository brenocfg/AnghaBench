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
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_PRECISION_8_8 ; 
 int /*<<< orphan*/  IsGoodVal (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

cmsBool  IsGoodFixed8_8(const char *title, cmsFloat64Number in, cmsFloat64Number out)
{
    return IsGoodVal(title, in, out, FIXED_PRECISION_8_8);
}