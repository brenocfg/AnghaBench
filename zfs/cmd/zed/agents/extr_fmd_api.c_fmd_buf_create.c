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
typedef  int /*<<< orphan*/  fmd_hdl_t ;
struct TYPE_3__ {size_t ci_bufsiz; int /*<<< orphan*/ * ci_bufptr; } ;
typedef  TYPE_1__ fmd_case_t ;

/* Variables and functions */
 int /*<<< orphan*/  FMD_SLEEP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fmd_hdl_alloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
fmd_buf_create(fmd_hdl_t *hdl, fmd_case_t *cp, const char *name, size_t size)
{
	assert(strcmp(name, "data") == 0);
	assert(cp->ci_bufptr == NULL);
	assert(size < (1024 * 1024));

	cp->ci_bufptr = fmd_hdl_alloc(hdl, size, FMD_SLEEP);
	cp->ci_bufsiz = size;
}