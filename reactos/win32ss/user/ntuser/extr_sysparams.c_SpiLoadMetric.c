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
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_METRIC ; 
 int /*<<< orphan*/  METRIC2REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG2METRIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpiLoadInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
INT
SpiLoadMetric(PCWSTR pwszValue, INT iValue)
{
    INT iRegVal;

    iRegVal = SpiLoadInt(KEY_METRIC, pwszValue, METRIC2REG(iValue));
    TRACE("Loaded metric setting '%S', iValue=%d(reg:%d), ret=%d(reg:%d)\n",
           pwszValue, iValue, METRIC2REG(iValue), REG2METRIC(iRegVal), iRegVal);
    return REG2METRIC(iRegVal);
}