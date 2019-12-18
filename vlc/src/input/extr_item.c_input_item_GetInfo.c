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
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ input_item_t ;
struct TYPE_7__ {char* psz_value; } ;
typedef  TYPE_2__ info_t ;
typedef  int /*<<< orphan*/  info_category_t ;

/* Variables and functions */
 int /*<<< orphan*/ * InputItemFindCat (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* info_category_FindInfo (int /*<<< orphan*/  const*,char const*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

char *input_item_GetInfo( input_item_t *p_i,
                          const char *psz_cat,
                          const char *psz_name )
{
    vlc_mutex_lock( &p_i->lock );

    const info_category_t *p_cat = InputItemFindCat( p_i, NULL, psz_cat );
    if( p_cat )
    {
        info_t *p_info = info_category_FindInfo( p_cat, psz_name );
        if( p_info && p_info->psz_value )
        {
            char *psz_ret = strdup( p_info->psz_value );
            vlc_mutex_unlock( &p_i->lock );
            return psz_ret;
        }
    }
    vlc_mutex_unlock( &p_i->lock );
    return strdup( "" );
}