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
struct wlr_surface {int dummy; } ;
struct wlr_box {int dummy; } ;
struct surface_iterator_data {int /*<<< orphan*/  user_data; int /*<<< orphan*/  rotation; int /*<<< orphan*/  output; int /*<<< orphan*/  (* user_iterator ) (int /*<<< orphan*/ ,struct wlr_surface*,struct wlr_box*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int get_surface_box (struct surface_iterator_data*,struct wlr_surface*,int,int,struct wlr_box*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct wlr_surface*,struct wlr_box*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void output_for_each_surface_iterator(struct wlr_surface *surface,
		int sx, int sy, void *_data) {
	struct surface_iterator_data *data = _data;

	struct wlr_box box;
	bool intersects = get_surface_box(data, surface, sx, sy, &box);
	if (!intersects) {
		return;
	}

	data->user_iterator(data->output, surface, &box, data->rotation,
		data->user_data);
}