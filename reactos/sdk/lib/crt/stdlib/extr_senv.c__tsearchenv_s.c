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
typedef  char _TCHAR ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ERANGE ; 
 scalar_t__ GetFileAttributes (char const*) ; 
 int /*<<< orphan*/  GetFullPathName (char const*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSVCRT_CHECK_PMT (int) ; 
 int /*<<< orphan*/  MSVCRT_INVALID_PMT (char*,int) ; 
 int /*<<< orphan*/  _dosmaperr (int /*<<< orphan*/ ) ; 
 int* _errno () ; 
 int /*<<< orphan*/  _set_errno (int) ; 
 int /*<<< orphan*/  _tcscat (char*,char const*) ; 
 int /*<<< orphan*/  _tcscpy (char*,char*) ; 
 int _tcslen (char*) ; 
 char* _tgetenv (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

int _tsearchenv_s(const _TCHAR* file, const _TCHAR* env, _TCHAR *buf, size_t count)
{
  _TCHAR *envVal, *penv;
  _TCHAR curPath[MAX_PATH];

  if (!MSVCRT_CHECK_PMT(file != NULL) || !MSVCRT_CHECK_PMT(buf != NULL) ||
      !MSVCRT_CHECK_PMT(count > 0))
  {
      *_errno() = EINVAL;
      return EINVAL;
  }

  *buf = '\0';

  /* Try CWD first */
  if (GetFileAttributes( file ) != INVALID_FILE_ATTRIBUTES)
  {
    GetFullPathName( file, MAX_PATH, buf, NULL );
    _dosmaperr(GetLastError());
    return 0;
  }

  /* Search given environment variable */
  envVal = _tgetenv(env);
  if (!envVal)
  {
    _set_errno(ENOENT);
    return ENOENT;
  }

  penv = envVal;

  do
  {
    _TCHAR *end = penv;

    while(*end && *end != ';') end++; /* Find end of next path */
    if (penv == end || !*penv)
    {
      _set_errno(ENOENT);
      return ENOENT;
    }
    memcpy(curPath, penv, (end - penv) * sizeof(_TCHAR));
    if (curPath[end - penv] != '/' && curPath[end - penv] != '\\')
    {
      curPath[end - penv] = '\\';
      curPath[end - penv + 1] = '\0';
    }
    else
      curPath[end - penv] = '\0';

    _tcscat(curPath, file);
    if (GetFileAttributes( curPath ) != INVALID_FILE_ATTRIBUTES)
    {
      if (_tcslen(curPath) + 1 > count)
      {
          MSVCRT_INVALID_PMT("buf[count] is too small", ERANGE);
          return ERANGE;
      }
      _tcscpy(buf, curPath);
      return 0;
    }
    penv = *end ? end + 1 : end;
  } while(1);

}