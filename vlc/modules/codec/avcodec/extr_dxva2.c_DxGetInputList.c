#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vlc_va_t ;
struct TYPE_8__ {int /*<<< orphan*/  d3ddec; } ;
typedef  TYPE_2__ vlc_va_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  pf_release; int /*<<< orphan*/ * list; int /*<<< orphan*/  count; } ;
typedef  TYPE_3__ input_list_t ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectXVideoDecoderService_GetDecoderDeviceGuids (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ReleaseInputList ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 

__attribute__((used)) static int DxGetInputList(vlc_va_t *va, input_list_t *p_list)
{
    vlc_va_sys_t *sys = va->sys;
    UINT input_count = 0;
    GUID *input_list = NULL;
    if (FAILED(IDirectXVideoDecoderService_GetDecoderDeviceGuids(sys->d3ddec,
                                                                 &input_count,
                                                                 &input_list))) {
        msg_Err(va, "IDirectXVideoDecoderService_GetDecoderDeviceGuids failed");
        return VLC_EGENERIC;
    }

    p_list->count = input_count;
    p_list->list = input_list;
    p_list->pf_release = ReleaseInputList;
    return VLC_SUCCESS;
}