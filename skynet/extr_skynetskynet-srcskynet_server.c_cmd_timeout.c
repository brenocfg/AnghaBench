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
struct skynet_context {char const* result; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int skynet_context_newsession (struct skynet_context*) ; 
 int /*<<< orphan*/  skynet_timeout (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sprintf (char const*,char*,int) ; 
 int strtol (char const*,char**,int) ; 

__attribute__((used)) static const char *
cmd_timeout(struct skynet_context * context, const char * param) {
	char * session_ptr = NULL;
	int ti = strtol(param, &session_ptr, 10);
	int session = skynet_context_newsession(context);
	skynet_timeout(context->handle, ti, session);
	sprintf(context->result, "%d", session);
	return context->result;
}