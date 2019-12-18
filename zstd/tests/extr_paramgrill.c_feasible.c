#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ cSpeed; scalar_t__ dSpeed; scalar_t__ cMem; } ;
typedef  TYPE_1__ constraint_t ;
struct TYPE_8__ {scalar_t__ cSize; } ;
struct TYPE_7__ {scalar_t__ cSpeed; scalar_t__ dSpeed; scalar_t__ cMem; scalar_t__ cSize; } ;
typedef  TYPE_2__ BMK_benchResult_t ;

/* Variables and functions */
 TYPE_3__ g_lvltarget ; 
 int /*<<< orphan*/  g_optmode ; 

__attribute__((used)) static int feasible(const BMK_benchResult_t results, const constraint_t target) {
    return (results.cSpeed >= target.cSpeed)
        && (results.dSpeed >= target.dSpeed)
        && (results.cMem <= target.cMem)
        && (!g_optmode || results.cSize <= g_lvltarget.cSize);
}