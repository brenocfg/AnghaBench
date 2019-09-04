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
typedef  scalar_t__ TCHAR ;
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int KEY_MAX_LEN ; 
 int REG_CLASS_NUMBER ; 
 scalar_t__ _T (char) ; 
 scalar_t__* _tcschr (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  _tcscmp (scalar_t__*,int /*<<< orphan*/ ) ; 
 int _tcslen (scalar_t__*) ; 
 int /*<<< orphan*/  _tcsncpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/ * reg_class_keys ; 
 int /*<<< orphan*/ * reg_class_names ; 

HKEY getRegClass(LPTSTR lpClass)
{
  LPTSTR classNameEnd;
  LPTSTR classNameBeg;
  int i;

  TCHAR lpClassCopy[KEY_MAX_LEN];

  if (lpClass == NULL)
    return (HKEY)ERROR_INVALID_PARAMETER;

  _tcsncpy(lpClassCopy, lpClass, KEY_MAX_LEN);

  classNameEnd  = _tcschr(lpClassCopy, _T('\\'));    /* The class name ends by '\' */
  if (!classNameEnd) {                          /* or the whole string */
      classNameEnd = lpClassCopy + _tcslen(lpClassCopy);
      if (classNameEnd[-1] == _T(']')) {
          classNameEnd--;
      }
  }
  *classNameEnd = _T('\0');                       /* Isolate the class name */
  if (lpClassCopy[0] == _T('[')) {
      classNameBeg = lpClassCopy + 1;
  } else {
      classNameBeg = lpClassCopy;
  }
  for (i = 0; i < REG_CLASS_NUMBER; i++) {
      if (!_tcscmp(classNameBeg, reg_class_names[i])) {
          return reg_class_keys[i];
      }
  }
  return (HKEY)ERROR_INVALID_PARAMETER;
}