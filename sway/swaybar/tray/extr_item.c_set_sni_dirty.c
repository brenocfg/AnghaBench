#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct swaybar_sni {TYPE_1__* tray; scalar_t__ max_size; scalar_t__ min_size; scalar_t__ target_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  bar; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bar_dirty (int /*<<< orphan*/ ) ; 
 scalar_t__ sni_ready (struct swaybar_sni*) ; 

__attribute__((used)) static void set_sni_dirty(struct swaybar_sni *sni) {
	if (sni_ready(sni)) {
		sni->target_size = sni->min_size = sni->max_size = 0; // invalidate previous icon
		set_bar_dirty(sni->tray->bar);
	}
}