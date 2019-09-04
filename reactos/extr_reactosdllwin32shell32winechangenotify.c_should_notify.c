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
typedef  int /*<<< orphan*/  LPCITEMIDLIST ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ ILIsEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ILIsParent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOL should_notify( LPCITEMIDLIST changed, LPCITEMIDLIST watched, BOOL sub )
{
    TRACE("%p %p %d\n", changed, watched, sub );
    if ( !watched )
        return FALSE;
    if (ILIsEqual( watched, changed ) )
        return TRUE;
    if( sub && ILIsParent( watched, changed, FALSE ) )
        return TRUE;
    return FALSE;
}