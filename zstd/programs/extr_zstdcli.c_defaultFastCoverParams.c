#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  params ;
struct TYPE_4__ {int d; int f; int steps; double splitPoint; int /*<<< orphan*/  shrinkDictMaxRegression; scalar_t__ shrinkDict; int /*<<< orphan*/  accel; } ;
typedef  TYPE_1__ ZDICT_fastCover_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ACCEL ; 
 int /*<<< orphan*/  kDefaultRegression ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ZDICT_fastCover_params_t defaultFastCoverParams(void)
{
    ZDICT_fastCover_params_t params;
    memset(&params, 0, sizeof(params));
    params.d = 8;
    params.f = 20;
    params.steps = 4;
    params.splitPoint = 0.75; /* different from default splitPoint of cover */
    params.accel = DEFAULT_ACCEL;
    params.shrinkDict = 0;
    params.shrinkDictMaxRegression = kDefaultRegression;
    return params;
}