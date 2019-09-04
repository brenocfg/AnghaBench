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
struct view {struct property* proplist; } ;
struct property {struct property* next; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

BOOL is_selected_prop( const struct view *view, const WCHAR *name )
{
    const struct property *prop = view->proplist;

    if (!prop) return TRUE;
    while (prop)
    {
        if (!strcmpiW( prop->name, name )) return TRUE;
        prop = prop->next;
    }
    return FALSE;
}