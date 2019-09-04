#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct view {scalar_t__ proplist; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 scalar_t__ SysStringLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_classname (struct view const*) ; 
 int /*<<< orphan*/ * build_proplist (struct view const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  count_key_columns (struct view const*) ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlenW (char const*) ; 

__attribute__((used)) static BSTR build_relpath( const struct view *view, UINT index, const WCHAR *name )
{
    static const WCHAR fmtW[] = {'%','s','.','%','s',0};
    BSTR class, proplist, ret = NULL;
    UINT num_keys, len;

    if (view->proplist) return NULL;

    if (!(class = build_classname( view ))) return NULL;
    if (!(num_keys = count_key_columns( view ))) return class;
    if (!(proplist = build_proplist( view, index, num_keys, &len ))) goto done;

    len += strlenW( fmtW ) + SysStringLen( class );
    if (!(ret = SysAllocStringLen( NULL, len ))) goto done;
    sprintfW( ret, fmtW, class, proplist );

done:
    SysFreeString( class );
    SysFreeString( proplist );
    return ret;
}