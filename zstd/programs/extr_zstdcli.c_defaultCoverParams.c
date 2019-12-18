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
struct TYPE_4__ {int d; int steps; double splitPoint; int /*<<< orphan*/  shrinkDictMaxRegression; scalar_t__ shrinkDict; } ;
typedef  TYPE_1__ ZDICT_cover_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  kDefaultRegression ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ZDICT_cover_params_t defaultCoverParams(void)
{
    ZDICT_cover_params_t params;
    memset(&params, 0, sizeof(params));
    params.d = 8;
    params.steps = 4;
    params.splitPoint = 1.0;
    params.shrinkDict = 0;
    params.shrinkDictMaxRegression = kDefaultRegression;
    return params;
}