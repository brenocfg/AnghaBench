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
struct swaybar_sni {char* status; scalar_t__ icon_pixmap; scalar_t__ icon_name; scalar_t__ attention_icon_pixmap; scalar_t__ attention_icon_name; } ;

/* Variables and functions */

__attribute__((used)) static bool sni_ready(struct swaybar_sni *sni) {
	return sni->status && (sni->status[0] == 'N' ? // NeedsAttention
			sni->attention_icon_name || sni->attention_icon_pixmap :
			sni->icon_name || sni->icon_pixmap);
}