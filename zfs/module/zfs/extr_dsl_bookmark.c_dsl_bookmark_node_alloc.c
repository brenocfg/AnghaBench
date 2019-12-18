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
struct TYPE_4__ {int /*<<< orphan*/  dbn_lock; int /*<<< orphan*/  dbn_dirty; int /*<<< orphan*/  dbn_name; } ;
typedef  TYPE_1__ dsl_bookmark_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_strdup (char*) ; 

__attribute__((used)) static dsl_bookmark_node_t *
dsl_bookmark_node_alloc(char *shortname)
{
	dsl_bookmark_node_t *dbn = kmem_alloc(sizeof (*dbn), KM_SLEEP);
	dbn->dbn_name = spa_strdup(shortname);
	dbn->dbn_dirty = B_FALSE;
	mutex_init(&dbn->dbn_lock, NULL, MUTEX_DEFAULT, NULL);
	return (dbn);
}