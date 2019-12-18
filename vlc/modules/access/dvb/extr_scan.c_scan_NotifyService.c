#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  p_cbdata; int /*<<< orphan*/  (* pf_notify_service ) (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ scan_t ;
struct TYPE_8__ {int /*<<< orphan*/  stickyref; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ scan_service_t ;

/* Variables and functions */
 int /*<<< orphan*/  scan_service_type_Supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void scan_NotifyService( scan_t *p_scan, scan_service_t *p_service, bool b_updated )
{
    if( !p_scan->pf_notify_service || !scan_service_type_Supported( p_service->type ) )
        return;
    p_service->stickyref = p_scan->pf_notify_service( p_scan, p_scan->p_cbdata,
                                                      p_service, p_service->stickyref,
                                                      b_updated );
}