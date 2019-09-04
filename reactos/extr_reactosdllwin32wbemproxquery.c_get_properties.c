#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct view {TYPE_2__* table; } ;
typedef  size_t UINT ;
struct TYPE_4__ {size_t num_cols; TYPE_1__* columns; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SAFEARRAY ;
typedef  int LONG ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * SafeArrayCreateVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  SafeArrayDestroy (int /*<<< orphan*/ *) ; 
 scalar_t__ SafeArrayPutElement (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_BSTR ; 
 int WBEM_FLAG_NONSYSTEM_ONLY ; 
 int WBEM_FLAG_SYSTEM_ONLY ; 
 size_t count_selected_properties (struct view const*) ; 
 scalar_t__ is_method (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  is_selected_prop (struct view const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_system_prop (int /*<<< orphan*/ ) ; 

HRESULT get_properties( const struct view *view, LONG flags, SAFEARRAY **props )
{
    SAFEARRAY *sa;
    BSTR str;
    UINT i, num_props = count_selected_properties( view );
    LONG j;

    if (!(sa = SafeArrayCreateVector( VT_BSTR, 0, num_props ))) return E_OUTOFMEMORY;

    for (i = 0, j = 0; i < view->table->num_cols; i++)
    {
        BOOL is_system;

        if (is_method( view->table, i )) continue;
        if (!is_selected_prop( view, view->table->columns[i].name )) continue;

        is_system = is_system_prop( view->table->columns[i].name );
        if ((flags & WBEM_FLAG_NONSYSTEM_ONLY) && is_system) continue;
        else if ((flags & WBEM_FLAG_SYSTEM_ONLY) && !is_system) continue;

        str = SysAllocString( view->table->columns[i].name );
        if (!str || SafeArrayPutElement( sa, &j, str ) != S_OK)
        {
            SysFreeString( str );
            SafeArrayDestroy( sa );
            return E_OUTOFMEMORY;
        }
        SysFreeString( str );
        j++;
    }
    *props = sa;
    return S_OK;
}