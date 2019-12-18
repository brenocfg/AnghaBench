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
struct check_items_order_data {int done_playing; scalar_t__ count; scalar_t__ index; } ;

/* Variables and functions */

__attribute__((used)) static inline void check_data_init(struct check_items_order_data *check)
{
    check->index = 0;
    check->count = 0;
    check->done_playing = false;
}