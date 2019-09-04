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
struct swaybar_sni {int /*<<< orphan*/  attention_icon_pixmap; int /*<<< orphan*/  attention_icon_name; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int sni_check_msg_sender (struct swaybar_sni*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sni_get_property_async (struct swaybar_sni*,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_new_attention_icon(sd_bus_message *msg, void *data,
		sd_bus_error *error) {
	struct swaybar_sni *sni = data;
	sni_get_property_async(sni, "AttentionIconName", "s", &sni->attention_icon_name);
	sni_get_property_async(sni, "AttentionIconPixmap", NULL, &sni->attention_icon_pixmap);
	return sni_check_msg_sender(sni, msg, "attention icon");
}