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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_2__ {int /*<<< orphan*/ * p_sys; int /*<<< orphan*/ * pf_seek; int /*<<< orphan*/  pf_block; int /*<<< orphan*/ * pf_read; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  psz_location; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  imem_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Block ; 
 int /*<<< orphan*/  CloseCommon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ControlAccess ; 
 scalar_t__ OpenCommon (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int var_InheritInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int OpenAccess(vlc_object_t *object)
{
    stream_t   *access = (stream_t *)object;
    imem_sys_t *sys;

    if (OpenCommon(object, &sys, access->psz_location))
        return VLC_EGENERIC;

    if (var_InheritInteger(object, "imem-cat") != 4) {
        CloseCommon(sys);
        return VLC_EGENERIC;
    }

    /* */
    access->pf_control = ControlAccess;
    access->pf_read    = NULL;
    access->pf_block   = Block;
    access->pf_seek    = NULL;
    access->p_sys      = sys;

    return VLC_SUCCESS;
}