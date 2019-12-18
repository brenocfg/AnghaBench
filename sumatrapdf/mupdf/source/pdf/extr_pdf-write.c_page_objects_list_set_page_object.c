#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int list_len; TYPE_4__* page_object_lists; } ;
typedef  TYPE_2__ pdf_write_state ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {TYPE_1__** page; } ;
struct TYPE_6__ {int page_object_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  expand_lists (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  page_objects_list_ensure (int /*<<< orphan*/ *,TYPE_4__**,int) ; 

__attribute__((used)) static void
page_objects_list_set_page_object(fz_context *ctx, pdf_write_state *opts, int page, int object)
{
	page_objects_list_ensure(ctx, &opts->page_object_lists, page+1);
	if (object >= opts->list_len)
		expand_lists(ctx, opts, object);
	opts->page_object_lists->page[page]->page_object_number = object;
}