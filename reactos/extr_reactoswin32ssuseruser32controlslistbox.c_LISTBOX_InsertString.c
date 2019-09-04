#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_6__ {int nb_items; int /*<<< orphan*/  self; } ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  const* LPCWSTR ;
typedef  TYPE_1__ LB_DESCR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HAS_STRINGS (TYPE_1__*) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LBN_ERRSPACE ; 
 int LB_ERRSPACE ; 
 int LISTBOX_InsertItem (TYPE_1__*,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SEND_NOTIFICATION (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,char*) ; 
 char* debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static LRESULT LISTBOX_InsertString( LB_DESCR *descr, INT index, LPCWSTR str )
{
    LPWSTR new_str = NULL;
    ULONG_PTR data = 0;
    LRESULT ret;

    if (HAS_STRINGS(descr))
    {
        static const WCHAR empty_stringW[] = { 0 };
        if (!str) str = empty_stringW;
        if (!(new_str = HeapAlloc( GetProcessHeap(), 0, (strlenW(str) + 1) * sizeof(WCHAR) )))
        {
            SEND_NOTIFICATION( descr, LBN_ERRSPACE );
            return LB_ERRSPACE;
        }
        strcpyW(new_str, str);
    }
    else data = (ULONG_PTR)str;

    if (index == -1) index = descr->nb_items;
    if ((ret = LISTBOX_InsertItem( descr, index, new_str, data )) != 0)
    {
        HeapFree( GetProcessHeap(), 0, new_str );
        return ret;
    }

    TRACE("[%p]: added item %d %s\n",
          descr->self, index, HAS_STRINGS(descr) ? debugstr_w(new_str) : "" );
    return index;
}