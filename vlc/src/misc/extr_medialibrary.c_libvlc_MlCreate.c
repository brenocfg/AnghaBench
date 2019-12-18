#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * p_module; int /*<<< orphan*/ * cbs; } ;
struct TYPE_6__ {TYPE_2__ m; int /*<<< orphan*/  lock; int /*<<< orphan*/  cbs; } ;
typedef  TYPE_1__ vlc_medialibrary_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callbacks ; 
 int /*<<< orphan*/ * module_need (TYPE_2__*,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  vlc_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_2__*) ; 

vlc_medialibrary_t* libvlc_MlCreate( libvlc_int_t* p_libvlc  )
{
    vlc_medialibrary_t *p_ml = vlc_custom_create( VLC_OBJECT( p_libvlc ),
                                                  sizeof( *p_ml ), "medialibrary" );
    if ( unlikely( p_ml == NULL ) )
        return NULL;
    vlc_mutex_init( &p_ml->lock );
    vlc_list_init( &p_ml->cbs );
    p_ml->m.cbs = &callbacks;
    p_ml->m.p_module = module_need( &p_ml->m, "medialibrary", NULL, false );
    if ( p_ml->m.p_module == NULL )
    {
        vlc_mutex_destroy( &p_ml->lock );
        vlc_object_delete(&p_ml->m);
        return NULL;
    }
    return p_ml;
}