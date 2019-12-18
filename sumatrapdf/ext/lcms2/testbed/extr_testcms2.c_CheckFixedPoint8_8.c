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
 int /*<<< orphan*/  TestSingleFixed8_8 (double) ; 

__attribute__((used)) static
cmsInt32Number CheckFixedPoint8_8(void)
{
    if (!TestSingleFixed8_8(1.0)) return 0;
    if (!TestSingleFixed8_8(2.0)) return 0;
    if (!TestSingleFixed8_8(1.23456)) return 0;
    if (!TestSingleFixed8_8(0.99999)) return 0;
    if (!TestSingleFixed8_8(0.1234567890123456789099999)) return 0;
    if (!TestSingleFixed8_8(+255.1234567890123456789099999)) return 0;

    return 1;
}