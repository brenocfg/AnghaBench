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
struct skynet_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  skynet_context_dispatchall (struct skynet_context*) ; 
 struct skynet_context* skynet_context_new (char*,char*) ; 
 int /*<<< orphan*/  skynet_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
bootstrap(struct skynet_context * logger, const char * cmdline) {
	int sz = strlen(cmdline);
	char name[sz+1];
	char args[sz+1];
	sscanf(cmdline, "%s %s", name, args);
	struct skynet_context *ctx = skynet_context_new(name, args);
	if (ctx == NULL) {
		skynet_error(NULL, "Bootstrap error : %s\n", cmdline);
		skynet_context_dispatchall(logger);
		exit(1);
	}
}