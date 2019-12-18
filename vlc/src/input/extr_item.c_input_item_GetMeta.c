#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_meta_type_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 char* input_item_GetMetaLocked (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

char *input_item_GetMeta( input_item_t *p_i, vlc_meta_type_t meta_type )
{
    vlc_mutex_lock( &p_i->lock );
    const char *value = input_item_GetMetaLocked( p_i, meta_type );
    char *psz = value ? strdup( value ) : NULL;
    vlc_mutex_unlock( &p_i->lock );
    return psz;
}