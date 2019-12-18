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
typedef  int /*<<< orphan*/  _TCHAR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 scalar_t__ GetCurrentDirectory (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  _dosmaperr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _set_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _tcsdup (int /*<<< orphan*/ *) ; 

_TCHAR* _tgetcwd(_TCHAR* buf, int size)
{
  _TCHAR dir[MAX_PATH];
  DWORD dir_len = GetCurrentDirectory(MAX_PATH,dir);

  if (dir_len == 0)
  {
    _dosmaperr(GetLastError());
    return NULL; /* FIXME: Real return value untested */
  }

  if (!buf)
  {
    return _tcsdup(dir);
  }

  if (dir_len >= (DWORD)size)
  {
    _set_errno(ERANGE);
    return NULL; /* buf too small */
  }

  _tcscpy(buf,dir);
  return buf;
}