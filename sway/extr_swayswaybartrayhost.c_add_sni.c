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
struct swaybar_tray {int /*<<< orphan*/  items; } ;
struct swaybar_sni {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_INFO ; 
 int /*<<< orphan*/  cmp_sni_id ; 
 struct swaybar_sni* create_sni (char*,struct swaybar_tray*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,struct swaybar_sni*) ; 
 int list_seq_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void add_sni(struct swaybar_tray *tray, char *id) {
	int idx = list_seq_find(tray->items, cmp_sni_id, id);
	if (idx == -1) {
		sway_log(SWAY_INFO, "Registering Status Notifier Item '%s'", id);
		struct swaybar_sni *sni = create_sni(id, tray);
		if (sni) {
			list_add(tray->items, sni);
		}
	}
}