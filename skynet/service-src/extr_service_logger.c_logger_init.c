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
struct logger {int close; int /*<<< orphan*/ * handle; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  logger_cb ; 
 int /*<<< orphan*/  skynet_callback (struct skynet_context*,struct logger*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_malloc (scalar_t__) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int
logger_init(struct logger * inst, struct skynet_context *ctx, const char * parm) {
	if (parm) {
		inst->handle = fopen(parm,"w");
		if (inst->handle == NULL) {
			return 1;
		}
		inst->filename = skynet_malloc(strlen(parm)+1);
		strcpy(inst->filename, parm);
		inst->close = 1;
	} else {
		inst->handle = stdout;
	}
	if (inst->handle) {
		skynet_callback(ctx, inst, logger_cb);
		return 0;
	}
	return 1;
}