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
struct dsl_pool {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_user_release_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dsl_pool*) ; 

void
dsl_dataset_user_release_tmp(struct dsl_pool *dp, nvlist_t *holds)
{
	ASSERT(dp != NULL);
	(void) dsl_dataset_user_release_impl(holds, NULL, dp);
}