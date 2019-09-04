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

/* Variables and functions */
#define  BT_FREEDOS 129 
 int BT_IMAGE ; 
#define  BT_REACTOS 128 
 int /*<<< orphan*/  HAS_KOLIBRIOS (int /*<<< orphan*/ ) ; 
 int boot_type ; 
 int /*<<< orphan*/  img_report ; 

__attribute__((used)) static __inline const char* bt_to_name(void) {
	switch (boot_type) {
	case BT_FREEDOS: return "FreeDOS";
	case BT_REACTOS: return "ReactOS";
	default:
		return ((boot_type == BT_IMAGE) && HAS_KOLIBRIOS(img_report)) ? "KolibriOS" : "Standard";
	}
}