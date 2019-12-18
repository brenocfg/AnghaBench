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
struct TYPE_3__ {char const* psz_name; int /*<<< orphan*/  lock; int /*<<< orphan*/  p_meta; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_STR (char const*) ; 
 char* strdup (char const*) ; 
 char* vlc_meta_Get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_meta_Title ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

char *input_item_GetTitleFbName( input_item_t *p_item )
{
    char *psz_ret;
    vlc_mutex_lock( &p_item->lock );

    if( !p_item->p_meta )
    {
        psz_ret = p_item->psz_name ? strdup( p_item->psz_name ) : NULL;
        vlc_mutex_unlock( &p_item->lock );
        return psz_ret;
    }

    const char *psz_title = vlc_meta_Get( p_item->p_meta, vlc_meta_Title );
    if( !EMPTY_STR( psz_title ) )
        psz_ret = strdup( psz_title );
    else
        psz_ret = p_item->psz_name ? strdup( p_item->psz_name ) : NULL;

    vlc_mutex_unlock( &p_item->lock );
    return psz_ret;
}