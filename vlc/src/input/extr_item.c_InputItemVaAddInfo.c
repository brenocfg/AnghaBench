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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_6__ {int /*<<< orphan*/  pp_categories; int /*<<< orphan*/  i_categories; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ input_item_t ;
struct TYPE_7__ {int /*<<< orphan*/  psz_value; } ;
typedef  TYPE_2__ info_t ;
typedef  int /*<<< orphan*/  info_category_t ;

/* Variables and functions */
 int /*<<< orphan*/ * InputItemFindCat (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  TAB_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * info_category_New (char const*) ; 
 TYPE_2__* info_category_VaAddInfo (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int InputItemVaAddInfo( input_item_t *p_i,
                               const char *psz_cat,
                               const char *psz_name,
                               const char *psz_format, va_list args )
{
    vlc_mutex_assert( &p_i->lock );

    info_category_t *p_cat = InputItemFindCat( p_i, NULL, psz_cat );
    if( !p_cat )
    {
        p_cat = info_category_New( psz_cat );
        if( !p_cat )
            return VLC_ENOMEM;
        TAB_APPEND(p_i->i_categories, p_i->pp_categories, p_cat);
    }
    info_t *p_info = info_category_VaAddInfo( p_cat, psz_name, psz_format, args );
    if( !p_info || !p_info->psz_value )
        return VLC_EGENERIC;
    return VLC_SUCCESS;
}