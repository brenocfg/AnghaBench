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
struct sway_container {size_t title_height; size_t title_baseline; } ;
struct TYPE_2__ {size_t font_baseline; size_t font_height; } ;

/* Variables and functions */
 TYPE_1__* config ; 

__attribute__((used)) static void find_font_height_iterator(struct sway_container *con, void *data) {
	size_t amount_below_baseline = con->title_height - con->title_baseline;
	size_t extended_height = config->font_baseline + amount_below_baseline;
	if (extended_height > config->font_height) {
		config->font_height = extended_height;
	}
}