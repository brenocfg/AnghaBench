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
typedef  scalar_t__ uint32_t ;
struct skynet_context {int /*<<< orphan*/  instance; int /*<<< orphan*/  mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  skynet_context_release (struct skynet_context*) ; 
 struct skynet_context* skynet_handle_grab (scalar_t__) ; 
 int /*<<< orphan*/  skynet_module_instance_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* strchr (char const*,char) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tohandle (struct skynet_context*,char const*) ; 

__attribute__((used)) static const char *
cmd_signal(struct skynet_context * context, const char * param) {
	uint32_t handle = tohandle(context, param);
	if (handle == 0)
		return NULL;
	struct skynet_context * ctx = skynet_handle_grab(handle);
	if (ctx == NULL)
		return NULL;
	param = strchr(param, ' ');
	int sig = 0;
	if (param) {
		sig = strtol(param, NULL, 0);
	}
	// NOTICE: the signal function should be thread safe.
	skynet_module_instance_signal(ctx->mod, ctx->instance, sig);

	skynet_context_release(ctx);
	return NULL;
}