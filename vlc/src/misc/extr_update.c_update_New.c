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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/ * psz_desc; int /*<<< orphan*/ * psz_url; } ;
struct TYPE_5__ {int /*<<< orphan*/ * p_pkey; int /*<<< orphan*/ * p_check; int /*<<< orphan*/ * p_download; TYPE_1__ release; int /*<<< orphan*/  p_libvlc; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ update_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  vlc_gcrypt_init () ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 

update_t *update_New( vlc_object_t *p_this )
{
    update_t *p_update;
    assert( p_this );

    p_update = (update_t *)malloc( sizeof( update_t ) );
    if( !p_update ) return NULL;

    vlc_mutex_init( &p_update->lock );

    p_update->p_libvlc = vlc_object_instance(p_this);

    p_update->release.psz_url = NULL;
    p_update->release.psz_desc = NULL;

    p_update->p_download = NULL;
    p_update->p_check = NULL;

    p_update->p_pkey = NULL;
    vlc_gcrypt_init();

    return p_update;
}