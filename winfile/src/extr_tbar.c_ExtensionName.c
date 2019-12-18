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
typedef  scalar_t__ UINT ;
struct TYPE_2__ {int /*<<< orphan*/  hModule; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ *) ; 
 scalar_t__ GetModuleFileName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXEXTNAME ; 
 int /*<<< orphan*/  StrNCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * StrRChr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char) ; 
 TYPE_1__* extensions ; 
 scalar_t__ iNumExtensions ; 

VOID
ExtensionName(int i, LPTSTR szName)
{
  TCHAR szFullName[256];
  LPTSTR lpName;

  *szName = TEXT('\0');

  if ((UINT)i<(UINT)iNumExtensions
   && GetModuleFileName(extensions[i].hModule, szFullName,
   COUNTOF(szFullName)) && (lpName=StrRChr (szFullName, NULL, TEXT('\\'))))
    StrNCpy(szName, lpName+1, MAXEXTNAME);
}