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
struct wlr_box {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 int /*<<< orphan*/  json_object_new_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object_new_object () ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static json_object *ipc_json_create_rect(struct wlr_box *box) {
	json_object *rect = json_object_new_object();

	json_object_object_add(rect, "x", json_object_new_int(box->x));
	json_object_object_add(rect, "y", json_object_new_int(box->y));
	json_object_object_add(rect, "width", json_object_new_int(box->width));
	json_object_object_add(rect, "height", json_object_new_int(box->height));

	return rect;
}