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
struct wl_listener {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arrange_root () ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 

__attribute__((used)) static void output_layout_handle_change(struct wl_listener *listener,
		void *data) {
	arrange_root();
	transaction_commit_dirty();
}