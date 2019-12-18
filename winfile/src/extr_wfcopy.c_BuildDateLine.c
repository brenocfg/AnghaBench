#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/  ftLastWriteTime; int /*<<< orphan*/  nFileSizeLow; } ;
struct TYPE_5__ {TYPE_1__ fd; } ;
typedef  TYPE_2__* PLFNDTA ;
typedef  scalar_t__ LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  PutDate (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  PutTime (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lstrcat (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lstrlen (scalar_t__) ; 
 int /*<<< orphan*/  szBytes ; 
 int /*<<< orphan*/  szSpace ; 
 int /*<<< orphan*/  wsprintf (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID
BuildDateLine(LPTSTR szTemp, PLFNDTA plfndta)
{
   wsprintf(szTemp, szBytes, plfndta->fd.nFileSizeLow);
   lstrcat(szTemp, szSpace);
   PutDate(&plfndta->fd.ftLastWriteTime, szTemp + lstrlen(szTemp));
   lstrcat(szTemp, szSpace);
   PutTime(&plfndta->fd.ftLastWriteTime, szTemp + lstrlen(szTemp));
}