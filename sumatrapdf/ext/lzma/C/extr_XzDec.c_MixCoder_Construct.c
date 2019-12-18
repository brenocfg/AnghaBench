#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* coders; scalar_t__ numCoders; scalar_t__ buf; int /*<<< orphan*/ * alloc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * p; } ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  TYPE_2__ CMixCoder ;

/* Variables and functions */
 int MIXCODER_NUM_FILTERS_MAX ; 

void MixCoder_Construct(CMixCoder *p, ISzAlloc *alloc)
{
  int i;
  p->alloc = alloc;
  p->buf = 0;
  p->numCoders = 0;
  for (i = 0; i < MIXCODER_NUM_FILTERS_MAX; i++)
    p->coders[i].p = NULL;
}