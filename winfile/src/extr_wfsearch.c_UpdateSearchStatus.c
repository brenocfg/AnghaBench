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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {scalar_t__ hThread; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  IDS_SEARCHING ; 
 int /*<<< orphan*/  IDS_SEARCHMSG ; 
 scalar_t__ MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int SST_FORMAT ; 
 int SST_RESOURCE ; 
 TYPE_1__ SearchInfo ; 
 int /*<<< orphan*/  SetStatusText (int,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  szNULL ; 

VOID
UpdateSearchStatus(HWND hwndLB, INT nCount)
{
   SetStatusText(0, SST_FORMAT|SST_RESOURCE, (LPWSTR) MAKEINTRESOURCE(IDS_SEARCHMSG), nCount);

   if (SearchInfo.hThread)
      SetStatusText(1, SST_RESOURCE, (LPWSTR) MAKEINTRESOURCE(IDS_SEARCHING));
   else
      SetStatusText(1, 0, szNULL);
}