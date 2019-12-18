#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  lpc_lib_handle; TYPE_1__* lpc_ops; } ;
typedef  TYPE_2__ libpc_handle_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int (* pco_pool_active ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zutil_pool_active(libpc_handle_t *hdl, const char *name, uint64_t guid,
    boolean_t *isactive)
{
	ASSERT(hdl->lpc_ops->pco_pool_active != NULL);

	int error = hdl->lpc_ops->pco_pool_active(hdl->lpc_lib_handle, name,
	    guid, isactive);

	return (error);
}