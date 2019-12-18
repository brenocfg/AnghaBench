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
struct TYPE_3__ {int refs; int chapter_num; void* doc; } ;
typedef  TYPE_1__ fz_html_key ;
typedef  int /*<<< orphan*/  fz_html ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_html_imp ; 
 int /*<<< orphan*/ * fz_find_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_html_store_type ; 

fz_html *fz_find_html(fz_context *ctx, void *doc, int chapter)
{
	fz_html_key key;

	key.refs = 1;
	key.doc = doc;
	key.chapter_num = chapter;
	return fz_find_item(ctx, &fz_drop_html_imp, &key, &fz_html_store_type);
}