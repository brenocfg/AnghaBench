#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_keystore_sys ;
struct TYPE_3__ {int /*<<< orphan*/  pf_remove; int /*<<< orphan*/  pf_find; int /*<<< orphan*/  pf_store; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vlc_keystore ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  Find ; 
 int /*<<< orphan*/  Remove ; 
 int /*<<< orphan*/  Store ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
Open(vlc_object_t *p_this)
{
    vlc_keystore *p_keystore = (vlc_keystore *)p_this;
    p_keystore->p_sys = calloc(1, sizeof(vlc_keystore_sys));
    if (!p_keystore->p_sys)
        return VLC_EGENERIC;

    vlc_mutex_init(&p_keystore->p_sys->lock);
    p_keystore->pf_store = Store;
    p_keystore->pf_find = Find;
    p_keystore->pf_remove = Remove;

    return VLC_SUCCESS;
}