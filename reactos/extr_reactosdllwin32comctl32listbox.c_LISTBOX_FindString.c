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
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_7__ {int nb_items; int style; TYPE_1__* items; int /*<<< orphan*/  locale; } ;
struct TYPE_6__ {char* str; scalar_t__ data; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  TYPE_1__ LB_ITEMDATA ;
typedef  TYPE_2__ LB_DESCR ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ HAS_STRINGS (TYPE_2__*) ; 
 int LBS_SORT ; 
 int LB_ERR ; 
 int LISTBOX_FindStringPos (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_lstrcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int strlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmpiW (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static INT LISTBOX_FindString( LB_DESCR *descr, INT start, LPCWSTR str, BOOL exact )
{
    INT i;
    LB_ITEMDATA *item;

    if (start >= descr->nb_items) start = -1;
    item = descr->items + start + 1;
    if (HAS_STRINGS(descr))
    {
        if (!str || ! str[0] ) return LB_ERR;
        if (exact)
        {
            for (i = start + 1; i < descr->nb_items; i++, item++)
                if (!LISTBOX_lstrcmpiW( descr->locale, str, item->str )) return i;
            for (i = 0, item = descr->items; i <= start; i++, item++)
                if (!LISTBOX_lstrcmpiW( descr->locale, str, item->str )) return i;
        }
        else
        {
 /* Special case for drives and directories: ignore prefix */
#define CHECK_DRIVE(item) \
    if ((item)->str[0] == '[') \
    { \
        if (!strncmpiW( str, (item)->str+1, len )) return i; \
        if (((item)->str[1] == '-') && !strncmpiW(str, (item)->str+2, len)) \
        return i; \
    }

            INT len = strlenW(str);
            for (i = start + 1; i < descr->nb_items; i++, item++)
            {
               if (!strncmpiW( str, item->str, len )) return i;
               CHECK_DRIVE(item);
            }
            for (i = 0, item = descr->items; i <= start; i++, item++)
            {
               if (!strncmpiW( str, item->str, len )) return i;
               CHECK_DRIVE(item);
            }
#undef CHECK_DRIVE
        }
    }
    else
    {
        if (exact && (descr->style & LBS_SORT))
            /* If sorted, use a WM_COMPAREITEM binary search */
            return LISTBOX_FindStringPos( descr, str, TRUE );

        /* Otherwise use a linear search */
        for (i = start + 1; i < descr->nb_items; i++, item++)
            if (item->data == (ULONG_PTR)str) return i;
        for (i = 0, item = descr->items; i <= start; i++, item++)
            if (item->data == (ULONG_PTR)str) return i;
    }
    return LB_ERR;
}