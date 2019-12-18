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
typedef  int /*<<< orphan*/  dmu_buf_user_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;

/* Variables and functions */
 void* dmu_buf_replace_user (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void *
dmu_buf_remove_user(dmu_buf_t *db_fake, dmu_buf_user_t *user)
{
	return (dmu_buf_replace_user(db_fake, user, NULL));
}