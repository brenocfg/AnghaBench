#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {char* lpc_desc; scalar_t__ lpc_printerr; scalar_t__ lpc_desc_active; } ;
typedef  TYPE_1__ libpc_handle_t ;
typedef  int /*<<< orphan*/  action ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zutil_verror(libpc_handle_t *hdl, const char *error, const char *fmt,
    va_list ap)
{
	char action[1024];

	(void) vsnprintf(action, sizeof (action), fmt, ap);

	if (hdl->lpc_desc_active)
		hdl->lpc_desc_active = B_FALSE;
	else
		hdl->lpc_desc[0] = '\0';

	if (hdl->lpc_printerr) {
		if (hdl->lpc_desc[0] != '\0')
			error = hdl->lpc_desc;

		(void) fprintf(stderr, "%s: %s\n", action, error);
	}
}