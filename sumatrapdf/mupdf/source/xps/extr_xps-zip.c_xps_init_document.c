#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int refs; int /*<<< orphan*/  lookup_metadata; int /*<<< orphan*/  load_page; int /*<<< orphan*/  count_pages; int /*<<< orphan*/  resolve_link; int /*<<< orphan*/  load_outline; int /*<<< orphan*/  drop_document; } ;
struct TYPE_5__ {TYPE_1__ super; } ;
typedef  TYPE_2__ xps_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  xps_count_pages ; 
 int /*<<< orphan*/  xps_drop_document ; 
 int /*<<< orphan*/  xps_load_outline ; 
 int /*<<< orphan*/  xps_load_page ; 
 int /*<<< orphan*/  xps_lookup_link_target ; 
 int /*<<< orphan*/  xps_lookup_metadata ; 

__attribute__((used)) static void
xps_init_document(fz_context *ctx, xps_document *doc)
{
	doc->super.refs = 1;
	doc->super.drop_document = xps_drop_document;
	doc->super.load_outline = xps_load_outline;
	doc->super.resolve_link = xps_lookup_link_target;
	doc->super.count_pages = xps_count_pages;
	doc->super.load_page = xps_load_page;
	doc->super.lookup_metadata = xps_lookup_metadata;
}