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
struct TYPE_8__ {TYPE_2__* p; } ;
typedef  TYPE_3__ vout_thread_t ;
struct TYPE_6__ {int /*<<< orphan*/ * chain_interactive; } ;
struct TYPE_7__ {TYPE_1__ filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ThreadDelFilterCallbacks ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_chain_ForEach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void ThreadDelAllFilterCallbacks(vout_thread_t *vout)
{
    assert(vout->p->filter.chain_interactive != NULL);
    filter_chain_ForEach(vout->p->filter.chain_interactive,
                         ThreadDelFilterCallbacks, vout);
}