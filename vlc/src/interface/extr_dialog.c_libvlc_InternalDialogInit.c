#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * p_ext_data; int /*<<< orphan*/ * pf_ext_update; int /*<<< orphan*/ * p_cbs_data; int /*<<< orphan*/  cbs; int /*<<< orphan*/  dialog_array; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_dialog_provider ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_5__ {TYPE_1__* p_dialog_provider; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__* libvlc_priv (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

int
libvlc_InternalDialogInit(libvlc_int_t *p_libvlc)
{
    assert(p_libvlc != NULL);
    vlc_dialog_provider *p_provider = malloc(sizeof(*p_provider));
    if (p_provider == NULL)
        return VLC_EGENERIC;

    vlc_mutex_init(&p_provider->lock);
    vlc_array_init(&p_provider->dialog_array);

    memset(&p_provider->cbs, 0, sizeof(p_provider->cbs));
    p_provider->p_cbs_data = NULL;

    p_provider->pf_ext_update = NULL;
    p_provider->p_ext_data = NULL;
    libvlc_priv(p_libvlc)->p_dialog_provider = p_provider;

    return VLC_SUCCESS;
}