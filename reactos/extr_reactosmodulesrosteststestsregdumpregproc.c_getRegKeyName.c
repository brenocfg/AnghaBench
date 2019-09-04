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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ENOUGH_MEMORY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int KEY_MAX_LEN ; 
 int /*<<< orphan*/  _T (char) ; 
 int /*<<< orphan*/ * _tcschr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _tcslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * currentKeyName ; 

LPTSTR getRegKeyName(LPTSTR lpLine)
{
  LPTSTR keyNameBeg;
  TCHAR  lpLineCopy[KEY_MAX_LEN];

  if (lpLine == NULL)
    return NULL;

  _tcscpy(lpLineCopy, lpLine);
  keyNameBeg = _tcschr(lpLineCopy, _T('\\'));    /* The key name start by '\' */
  if (keyNameBeg) {
      LPTSTR keyNameEnd;

      keyNameBeg++;                             /* is not part of the name */
      keyNameEnd = _tcschr(lpLineCopy, _T(']'));
      if (keyNameEnd) {
          *keyNameEnd = _T('\0');               /* remove ']' from the key name */
      }
  } else {
      keyNameBeg = lpLineCopy + _tcslen(lpLineCopy); /* branch - empty string */
  }
  currentKeyName = HeapAlloc(GetProcessHeap(), 0, (_tcslen(keyNameBeg)+1)*sizeof(TCHAR));
  CHECK_ENOUGH_MEMORY(currentKeyName);
  _tcscpy(currentKeyName, keyNameBeg);
  return currentKeyName;
}