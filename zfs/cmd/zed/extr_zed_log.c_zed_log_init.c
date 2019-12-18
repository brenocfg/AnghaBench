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
struct TYPE_2__ {char const* identity; int* pipe_fd; } ;

/* Variables and functions */
 TYPE_1__ _ctx ; 
 char* strrchr (char const*,char) ; 

void
zed_log_init(const char *identity)
{
	if (identity) {
		const char *p = strrchr(identity, '/');
		_ctx.identity = (p != NULL) ? p + 1 : identity;
	} else {
		_ctx.identity = NULL;
	}
	_ctx.pipe_fd[0] = -1;
	_ctx.pipe_fd[1] = -1;
}