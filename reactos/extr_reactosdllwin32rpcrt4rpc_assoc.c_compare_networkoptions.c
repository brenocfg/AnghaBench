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
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL compare_networkoptions(LPCWSTR opts1, LPCWSTR opts2)
{
    if ((opts1 == NULL) && (opts2 == NULL))
        return TRUE;
    if ((opts1 == NULL) || (opts2 == NULL))
        return FALSE;
    return !strcmpW(opts1, opts2);
}