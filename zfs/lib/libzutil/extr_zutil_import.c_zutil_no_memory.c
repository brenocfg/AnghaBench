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
typedef  int /*<<< orphan*/  libpc_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EZFS_NOMEM ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  zutil_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
zutil_no_memory(libpc_handle_t *hdl)
{
	zutil_error(hdl, EZFS_NOMEM, "internal error");
	exit(1);
}