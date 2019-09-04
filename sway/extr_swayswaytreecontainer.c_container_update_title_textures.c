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
struct sway_container {int /*<<< orphan*/  title_urgent; int /*<<< orphan*/  title_unfocused; int /*<<< orphan*/  title_focused_inactive; int /*<<< orphan*/  title_focused; } ;
struct TYPE_3__ {int /*<<< orphan*/  urgent; int /*<<< orphan*/  unfocused; int /*<<< orphan*/  focused_inactive; int /*<<< orphan*/  focused; } ;
struct TYPE_4__ {TYPE_1__ border_colors; } ;

/* Variables and functions */
 TYPE_2__* config ; 
 int /*<<< orphan*/  container_damage_whole (struct sway_container*) ; 
 int /*<<< orphan*/  update_title_texture (struct sway_container*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void container_update_title_textures(struct sway_container *container) {
	update_title_texture(container, &container->title_focused,
			&config->border_colors.focused);
	update_title_texture(container, &container->title_focused_inactive,
			&config->border_colors.focused_inactive);
	update_title_texture(container, &container->title_unfocused,
			&config->border_colors.unfocused);
	update_title_texture(container, &container->title_urgent,
			&config->border_colors.urgent);
	container_damage_whole(container);
}