#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  szDir; int /*<<< orphan*/ * hwnd; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MAXHISTORY ; 
 scalar_t__ TRUE ; 
 int historyCur ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* rghistoryDir ; 

BOOL
GetPrevHistoryDir(BOOL forward, HWND *phwnd, LPWSTR szDir)
{
	DWORD historyNext = (historyCur + 1) % MAXHISTORY;
	DWORD historyPrev = (historyCur == 0 ? MAXHISTORY : historyCur )- 1;
	DWORD historyT = forward ? historyNext : historyPrev;

	if (rghistoryDir[historyT].hwnd == NULL)
		return FALSE;
	
	historyCur = historyT;

	*phwnd = rghistoryDir[historyCur].hwnd;  
	lstrcpy(szDir, rghistoryDir[historyCur].szDir);
	return TRUE;
}