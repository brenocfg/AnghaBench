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
struct TYPE_4__ {int /*<<< orphan*/  cs; } ;
struct TYPE_5__ {TYPE_1__ mtProgress; int /*<<< orphan*/  cs; int /*<<< orphan*/ * threads; } ;
typedef  TYPE_2__ CMtCoder ;

/* Variables and functions */
 int /*<<< orphan*/  CMtThread_Destruct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CriticalSection_Delete (int /*<<< orphan*/ *) ; 
 unsigned int NUM_MT_CODER_THREADS_MAX ; 

void MtCoder_Destruct(CMtCoder* p)
{
  unsigned i;
  for (i = 0; i < NUM_MT_CODER_THREADS_MAX; i++)
    CMtThread_Destruct(&p->threads[i]);
  CriticalSection_Delete(&p->cs);
  CriticalSection_Delete(&p->mtProgress.cs);
}