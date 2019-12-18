#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_8__ {scalar_t__ mfplat_dll; } ;
struct TYPE_7__ {TYPE_3__ mf_handle; } ;
typedef  TYPE_2__ decoder_sys_t ;
typedef  TYPE_3__ MFHandle ;

/* Variables and functions */
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  DestroyMFT (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void Close(vlc_object_t *p_this)
{
    decoder_t *p_dec = (decoder_t *)p_this;
    decoder_sys_t *p_sys = p_dec->p_sys;
    MFHandle *mf = &p_sys->mf_handle;

    DestroyMFT(p_dec);

    if (mf->mfplat_dll)
        FreeLibrary(mf->mfplat_dll);

    free(p_sys);

    CoUninitialize();
}