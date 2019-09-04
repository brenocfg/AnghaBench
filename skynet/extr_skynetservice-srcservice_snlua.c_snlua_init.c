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
typedef  int /*<<< orphan*/  uint32_t ;
struct snlua {int dummy; } ;
struct skynet_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTYPE_TAG_DONTCOPY ; 
 int /*<<< orphan*/  launch_cb ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  skynet_callback (struct skynet_context*,struct snlua*,int /*<<< orphan*/ ) ; 
 char* skynet_command (struct skynet_context*,char*,int /*<<< orphan*/ *) ; 
 char* skynet_malloc (int) ; 
 int /*<<< orphan*/  skynet_send (struct skynet_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int) ; 

int
snlua_init(struct snlua *l, struct skynet_context *ctx, const char * args) {
	int sz = strlen(args);
	char * tmp = skynet_malloc(sz);
	memcpy(tmp, args, sz);
	skynet_callback(ctx, l , launch_cb);
	const char * self = skynet_command(ctx, "REG", NULL);
	uint32_t handle_id = strtoul(self+1, NULL, 16);
	// it must be first message
	skynet_send(ctx, 0, handle_id, PTYPE_TAG_DONTCOPY,0, tmp, sz);
	return 0;
}