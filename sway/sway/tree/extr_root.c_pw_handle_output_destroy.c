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
struct wl_listener {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct pid_workspace {TYPE_1__ output_destroy; int /*<<< orphan*/ * output; } ;

/* Variables and functions */
 int /*<<< orphan*/  output_destroy ; 
 struct pid_workspace* pw ; 
 struct pid_workspace* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pw_handle_output_destroy(struct wl_listener *listener, void *data) {
	struct pid_workspace *pw = wl_container_of(listener, pw, output_destroy);
	pw->output = NULL;
	wl_list_remove(&pw->output_destroy.link);
	wl_list_init(&pw->output_destroy.link);
}