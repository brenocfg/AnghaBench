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
struct TYPE_3__ {int /*<<< orphan*/  lDeadBand; int /*<<< orphan*/  dwNegativeSaturation; int /*<<< orphan*/  dwPositiveSaturation; int /*<<< orphan*/  lNegativeCoefficient; int /*<<< orphan*/  lPositiveCoefficient; int /*<<< orphan*/  lOffset; } ;
typedef  TYPE_1__* LPCDICONDITION ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _dump_DICONDITION(LPCDICONDITION frc)
{
    TRACE("Condition has offset %d, pos/neg coefficients %d and %d, pos/neg saturations %d and %d, deadband %d\n",
          frc->lOffset, frc->lPositiveCoefficient, frc->lNegativeCoefficient,
          frc->dwPositiveSaturation, frc->dwNegativeSaturation, frc->lDeadBand);
}