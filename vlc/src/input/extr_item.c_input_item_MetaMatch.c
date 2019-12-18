#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_meta_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  p_meta; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 scalar_t__ strcasestr (char const*,char const*) ; 
 char* vlc_meta_Get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

bool input_item_MetaMatch( input_item_t *p_i,
                           vlc_meta_type_t meta_type, const char *psz )
{
    vlc_mutex_lock( &p_i->lock );

    if( !p_i->p_meta )
    {
        vlc_mutex_unlock( &p_i->lock );
        return false;
    }
    const char *psz_meta = vlc_meta_Get( p_i->p_meta, meta_type );
    bool b_ret = psz_meta && strcasestr( psz_meta, psz );

    vlc_mutex_unlock( &p_i->lock );

    return b_ret;
}