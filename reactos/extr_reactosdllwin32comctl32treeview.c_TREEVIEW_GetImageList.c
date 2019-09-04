#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
struct TYPE_3__ {int /*<<< orphan*/  himlState; int /*<<< orphan*/  himlNormal; } ;
typedef  TYPE_1__ TREEVIEW_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
#define  TVSIL_NORMAL 129 
#define  TVSIL_STATE 128 

__attribute__((used)) static LRESULT
TREEVIEW_GetImageList(const TREEVIEW_INFO *infoPtr, WPARAM wParam)
{
    TRACE("\n");

    switch (wParam)
    {
    case TVSIL_NORMAL:
	return (LRESULT)infoPtr->himlNormal;

    case TVSIL_STATE:
	return (LRESULT)infoPtr->himlState;

    default:
	return 0;
    }
}