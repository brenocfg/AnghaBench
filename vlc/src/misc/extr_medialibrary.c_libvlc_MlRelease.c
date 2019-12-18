#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  p_module; } ;
struct TYPE_5__ {TYPE_2__ m; int /*<<< orphan*/  lock; int /*<<< orphan*/  cbs; } ;
typedef  TYPE_1__ vlc_medialibrary_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_unneed (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_list_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_2__*) ; 

void libvlc_MlRelease( vlc_medialibrary_t* p_ml )
{
    assert( p_ml != NULL );
    module_unneed( &p_ml->m, p_ml->m.p_module );
    assert( vlc_list_is_empty( &p_ml->cbs ) );
    vlc_mutex_destroy( &p_ml->lock );
    vlc_object_delete(&p_ml->m);
}