#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sway_container {int /*<<< orphan*/  marks_urgent; int /*<<< orphan*/  marks_unfocused; int /*<<< orphan*/  marks_focused_inactive; int /*<<< orphan*/  marks_focused; } ;
struct TYPE_3__ {int /*<<< orphan*/  urgent; int /*<<< orphan*/  unfocused; int /*<<< orphan*/  focused_inactive; int /*<<< orphan*/  focused; } ;
struct TYPE_4__ {TYPE_1__ border_colors; int /*<<< orphan*/  show_marks; } ;

/* Variables and functions */
 TYPE_2__* config ; 
 int /*<<< orphan*/  container_damage_whole (struct sway_container*) ; 
 int /*<<< orphan*/  update_marks_texture (struct sway_container*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void container_update_marks_textures(struct sway_container *con) {
	if (!config->show_marks) {
		return;
	}
	update_marks_texture(con, &con->marks_focused,
			&config->border_colors.focused);
	update_marks_texture(con, &con->marks_focused_inactive,
			&config->border_colors.focused_inactive);
	update_marks_texture(con, &con->marks_unfocused,
			&config->border_colors.unfocused);
	update_marks_texture(con, &con->marks_urgent,
			&config->border_colors.urgent);
	container_damage_whole(con);
}