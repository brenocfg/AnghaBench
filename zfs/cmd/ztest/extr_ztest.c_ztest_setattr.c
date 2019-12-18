#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ztest_ds_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {scalar_t__ lr_mode; scalar_t__ lr_size; int /*<<< orphan*/  lr_foid; } ;
typedef  TYPE_1__ lr_setattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 TYPE_1__* ztest_lr_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ztest_lr_free (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int ztest_replay_setattr (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ztest_setattr(ztest_ds_t *zd, uint64_t object)
{
	lr_setattr_t *lr;
	int error;

	lr = ztest_lr_alloc(sizeof (*lr), NULL);

	lr->lr_foid = object;
	lr->lr_size = 0;
	lr->lr_mode = 0;

	error = ztest_replay_setattr(zd, lr, B_FALSE);

	ztest_lr_free(lr, sizeof (*lr), NULL);

	return (error);
}