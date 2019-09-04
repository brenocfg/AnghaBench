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
struct view {int dummy; } ;
struct line {int /*<<< orphan*/  type; struct help* data; } ;
struct keymap {int hidden; } ;
struct help {struct keymap* keymap; } ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_SECTION ; 
#define  REQ_ENTER 129 
 int REQ_NONE ; 
#define  REQ_REFRESH 128 
 int /*<<< orphan*/  refresh_view (struct view*) ; 

__attribute__((used)) static enum request
help_request(struct view *view, enum request request, struct line *line)
{
	struct help *help = line->data;

	switch (request) {
	case REQ_ENTER:
		if (line->type == LINE_SECTION) {
			struct keymap *keymap = help->keymap;

			keymap->hidden = !keymap->hidden;
			refresh_view(view);
		}
		return REQ_NONE;

	case REQ_REFRESH:
		refresh_view(view);
		return REQ_NONE;

	default:
		return request;
	}
}