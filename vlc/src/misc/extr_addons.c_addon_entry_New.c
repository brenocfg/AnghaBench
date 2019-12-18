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
struct TYPE_5__ {int /*<<< orphan*/  files; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ addon_entry_t ;
struct TYPE_6__ {TYPE_1__ entry; int /*<<< orphan*/  rc; } ;
typedef  TYPE_2__ addon_entry_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_INIT (int /*<<< orphan*/ ) ; 
 TYPE_2__* calloc (int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_atomic_rc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

addon_entry_t * addon_entry_New(void)
{
    addon_entry_owner_t *owner = calloc( 1, sizeof(addon_entry_owner_t) );
    if( unlikely(owner == NULL) )
        return NULL;

    vlc_atomic_rc_init( &owner->rc );

    addon_entry_t *p_entry = &owner->entry;
    vlc_mutex_init( &p_entry->lock );
    ARRAY_INIT( p_entry->files );
    return p_entry;
}