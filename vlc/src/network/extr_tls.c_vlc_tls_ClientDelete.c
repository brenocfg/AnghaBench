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
struct TYPE_8__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ vlc_tls_client_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* destroy ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_objres_clear (int /*<<< orphan*/ ) ; 

void vlc_tls_ClientDelete(vlc_tls_client_t *crd)
{
    if (crd == NULL)
        return;

    crd->ops->destroy(crd);
    vlc_objres_clear(VLC_OBJECT(crd));
    vlc_object_delete(crd);
}