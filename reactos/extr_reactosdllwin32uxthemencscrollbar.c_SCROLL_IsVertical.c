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
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  SB_HORZ 129 
#define  SB_VERT 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL SCROLL_IsVertical(HWND hwnd, INT nBar)
{
    switch(nBar)
    {
    case SB_HORZ:
        return FALSE;
    case SB_VERT:
        return TRUE;
    default:
        assert(FALSE);
        return FALSE;
    }
}