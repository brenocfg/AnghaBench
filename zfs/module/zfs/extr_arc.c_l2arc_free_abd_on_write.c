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
struct TYPE_4__ {size_t l2df_size; int /*<<< orphan*/  l2df_type; int /*<<< orphan*/ * l2df_abd; } ;
typedef  TYPE_1__ l2arc_data_free_t ;
typedef  int /*<<< orphan*/  arc_buf_contents_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2arc_free_on_write ; 
 int /*<<< orphan*/  l2arc_free_on_write_mtx ; 
 int /*<<< orphan*/  list_insert_head (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2arc_free_abd_on_write(abd_t *abd, size_t size, arc_buf_contents_t type)
{
	l2arc_data_free_t *df = kmem_alloc(sizeof (*df), KM_SLEEP);

	df->l2df_abd = abd;
	df->l2df_size = size;
	df->l2df_type = type;
	mutex_enter(&l2arc_free_on_write_mtx);
	list_insert_head(l2arc_free_on_write, df);
	mutex_exit(&l2arc_free_on_write_mtx);
}