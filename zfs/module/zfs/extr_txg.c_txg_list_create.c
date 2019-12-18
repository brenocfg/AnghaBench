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
struct TYPE_3__ {size_t tl_offset; int /*<<< orphan*/ ** tl_head; int /*<<< orphan*/ * tl_spa; int /*<<< orphan*/  tl_lock; } ;
typedef  TYPE_1__ txg_list_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int TXG_SIZE ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
txg_list_create(txg_list_t *tl, spa_t *spa, size_t offset)
{
	int t;

	mutex_init(&tl->tl_lock, NULL, MUTEX_DEFAULT, NULL);

	tl->tl_offset = offset;
	tl->tl_spa = spa;

	for (t = 0; t < TXG_SIZE; t++)
		tl->tl_head[t] = NULL;
}