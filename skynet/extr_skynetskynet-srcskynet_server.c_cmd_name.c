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
struct skynet_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,char*) ; 
 char const* skynet_handle_namehandle (scalar_t__,char*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,char*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const char *
cmd_name(struct skynet_context * context, const char * param) {
	int size = strlen(param);
	char name[size+1];
	char handle[size+1];
	sscanf(param,"%s %s",name,handle);
	if (handle[0] != ':') {
		return NULL;
	}
	uint32_t handle_id = strtoul(handle+1, NULL, 16);
	if (handle_id == 0) {
		return NULL;
	}
	if (name[0] == '.') {
		return skynet_handle_namehandle(handle_id, name + 1);
	} else {
		skynet_error(context, "Can't set global name %s in C", name);
	}
	return NULL;
}