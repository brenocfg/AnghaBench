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
struct skynet_context {void* cb_ud; int /*<<< orphan*/  cb; } ;
typedef  int /*<<< orphan*/  skynet_cb ;

/* Variables and functions */

void 
skynet_callback(struct skynet_context * context, void *ud, skynet_cb cb) {
	context->cb = cb;
	context->cb_ud = ud;
}