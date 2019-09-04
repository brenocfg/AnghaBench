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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__* LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ _T (char) ; 
 int /*<<< orphan*/  _tcscpy (scalar_t__*,scalar_t__*) ; 
 int _tcslen (scalar_t__*) ; 

LPTSTR getArg(LPTSTR arg)
{
  LPTSTR tmp = NULL;
  ULONG len;

  if (arg == NULL) return NULL;

  // Get rid of surrounding quotes
  len = _tcslen(arg);
  if (arg[len-1] == _T('\"')) arg[len-1] = _T('\0');
  if (arg[0]     == _T('\"')) arg++;
  tmp = HeapAlloc(GetProcessHeap(), 0, (_tcslen(arg)+1) * sizeof(TCHAR));
  _tcscpy(tmp, arg);
  return tmp;
}