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
typedef  int /*<<< orphan*/  time_t ;
struct utimbuf {int /*<<< orphan*/  modtime; int /*<<< orphan*/  actime; } ;
struct tm {scalar_t__ tm_sec; scalar_t__ tm_min; scalar_t__ tm_hour; scalar_t__ tm_mday; scalar_t__ tm_wday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  void* WORD ;
struct TYPE_3__ {scalar_t__ wMilliseconds; void* wSecond; void* wMinute; void* wHour; void* wDay; void* wDayOfWeek; void* wMonth; void* wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_FLAG_BACKUP_SEMANTICS ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int GetVersion () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LocalFileTimeToFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ SetFileTime (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int utime (char*,struct utimbuf*) ; 

int setfiletime (char *fname,time_t ftime)
{
#ifdef WIN32
  static int isWinNT = -1;
  SYSTEMTIME st;
  FILETIME locft, modft;
  struct tm *loctm;
  HANDLE hFile;
  int result;

  loctm = localtime(&ftime);
  if (loctm == NULL)
    return -1;

  st.wYear         = (WORD)loctm->tm_year + 1900;
  st.wMonth        = (WORD)loctm->tm_mon + 1;
  st.wDayOfWeek    = (WORD)loctm->tm_wday;
  st.wDay          = (WORD)loctm->tm_mday;
  st.wHour         = (WORD)loctm->tm_hour;
  st.wMinute       = (WORD)loctm->tm_min;
  st.wSecond       = (WORD)loctm->tm_sec;
  st.wMilliseconds = 0;
  if (!SystemTimeToFileTime(&st, &locft) ||
      !LocalFileTimeToFileTime(&locft, &modft))
    return -1;

  if (isWinNT < 0)
    isWinNT = (GetVersion() < 0x80000000) ? 1 : 0;
  hFile = CreateFile(fname, GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
                     (isWinNT ? FILE_FLAG_BACKUP_SEMANTICS : 0),
                     NULL);
  if (hFile == INVALID_HANDLE_VALUE)
    return -1;
  result = SetFileTime(hFile, NULL, NULL, &modft) ? 0 : -1;
  CloseHandle(hFile);
  return result;
#else
  struct utimbuf settime;

  settime.actime = settime.modtime = ftime;
  return utime(fname,&settime);
#endif
}