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
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GA_PARENT ; 
 int /*<<< orphan*/  GA_ROOT ; 
 int /*<<< orphan*/  GA_ROOTOWNER ; 
 int /*<<< orphan*/  GWLP_HWNDPARENT ; 
 int /*<<< orphan*/  GW_OWNER ; 
 scalar_t__ GetParent (scalar_t__) ; 
 scalar_t__ GetWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowLongPtrA (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ pGetAncestor (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_parents( HWND hwnd, HWND ga_parent, HWND gwl_parent, HWND get_parent,
                           HWND gw_owner, HWND ga_root, HWND ga_root_owner )
{
    HWND res;

    if (pGetAncestor)
    {
        res = pGetAncestor( hwnd, GA_PARENT );
        ok( res == ga_parent, "Wrong result for GA_PARENT %p expected %p\n", res, ga_parent );
    }
    res = (HWND)GetWindowLongPtrA( hwnd, GWLP_HWNDPARENT );
    ok( res == gwl_parent, "Wrong result for GWL_HWNDPARENT %p expected %p\n", res, gwl_parent );
    res = GetParent( hwnd );
    ok( res == get_parent, "Wrong result for GetParent %p expected %p\n", res, get_parent );
    res = GetWindow( hwnd, GW_OWNER );
    ok( res == gw_owner, "Wrong result for GW_OWNER %p expected %p\n", res, gw_owner );
    if (pGetAncestor)
    {
        res = pGetAncestor( hwnd, GA_ROOT );
        ok( res == ga_root, "Wrong result for GA_ROOT %p expected %p\n", res, ga_root );
        res = pGetAncestor( hwnd, GA_ROOTOWNER );
        ok( res == ga_root_owner, "Wrong result for GA_ROOTOWNER %p expected %p\n", res, ga_root_owner );
    }
}