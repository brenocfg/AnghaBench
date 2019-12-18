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
struct menu_data {int /*<<< orphan*/  menu; int /*<<< orphan*/  s; int /*<<< orphan*/  data; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * item; } ;
struct client {struct menu_data* overlay_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYC_NONE ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  cmdq_continue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct menu_data*) ; 
 int /*<<< orphan*/  menu_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
menu_free_cb(struct client *c)
{
	struct menu_data	*md = c->overlay_data;

	if (md->item != NULL)
		cmdq_continue(md->item);

	if (md->cb != NULL)
		md->cb(md->menu, UINT_MAX, KEYC_NONE, md->data);

	screen_free(&md->s);
	menu_free(md->menu);
	free(md);
}