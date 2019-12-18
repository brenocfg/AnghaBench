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
struct TYPE_3__ {int /*<<< orphan*/  mmp_thread_lock; } ;
typedef  TYPE_1__ mmp_thread_t ;
typedef  int /*<<< orphan*/  callb_cpr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALLB_CPR_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  callb_generic_cpr ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mmp_thread_enter(mmp_thread_t *mmp, callb_cpr_t *cpr)
{
	CALLB_CPR_INIT(cpr, &mmp->mmp_thread_lock, callb_generic_cpr, FTAG);
	mutex_enter(&mmp->mmp_thread_lock);
}