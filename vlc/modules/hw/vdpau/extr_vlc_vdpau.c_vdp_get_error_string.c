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
struct TYPE_4__ {char const* (* get_error_string ) (scalar_t__) ;} ;
struct TYPE_5__ {TYPE_1__ vt; int /*<<< orphan*/ ** funcs; } ;
typedef  TYPE_2__ vdp_t ;
typedef  scalar_t__ VdpStatus ;

/* Variables and functions */
 size_t VDP_FUNC_ID_GET_ERROR_STRING ; 
 scalar_t__ VDP_STATUS_OK ; 
 char const* stub1 (scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

const char *vdp_get_error_string(const vdp_t *vdp, VdpStatus status)
{
    if (unlikely(vdp->funcs[VDP_FUNC_ID_GET_ERROR_STRING] == NULL))
        return (status != VDP_STATUS_OK) ? "Unknown error" : "No error";
    return vdp->vt.get_error_string(status);
}