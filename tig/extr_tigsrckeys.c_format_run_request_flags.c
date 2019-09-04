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
struct TYPE_2__ {scalar_t__ quick; scalar_t__ echo; scalar_t__ exit; scalar_t__ confirm; scalar_t__ silent; scalar_t__ internal; } ;
struct run_request {TYPE_1__ flags; } ;
typedef  int /*<<< orphan*/  flags ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

const char *
format_run_request_flags(const struct run_request *req)
{
	static char flags[8];
	int flagspos = 0;

	memset(flags, 0, sizeof(flags));

	if (req->flags.internal)
		flags[flagspos++] = ':';
	else
		flags[flagspos] = '!'; /* Optional, if other flags are defined */

	if (req->flags.silent)
	    flags[flagspos++] = '@';
	if (req->flags.confirm)
	    flags[flagspos++] = '?';
	if (req->flags.exit)
		flags[flagspos++] = '<';
	if (req->flags.echo)
		flags[flagspos++] = '+';
	if (req->flags.quick)
		flags[flagspos++] = '>';
	if (flagspos > 1)
		flags[flagspos++] = 0;

	return flags;
}