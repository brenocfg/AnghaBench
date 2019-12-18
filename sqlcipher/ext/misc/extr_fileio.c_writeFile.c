#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {void* tv_sec; scalar_t__ tv_usec; } ;
struct timespec {void* tv_sec; scalar_t__ tv_nsec; } ;
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int mode_t ;
struct TYPE_5__ {int dwHighDateTime; scalar_t__ dwLowDateTime; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  scalar_t__ LPWSTR ;
typedef  int LONGLONG ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_1__ FILETIME ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  FILE_FLAG_BACKUP_SEMANTICS ; 
 int /*<<< orphan*/  FILE_WRITE_ATTRIBUTES ; 
 int /*<<< orphan*/  GetSystemTime (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int Int32x32To64 (scalar_t__,int) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 int /*<<< orphan*/  SetFileTime (scalar_t__,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ chmod (char const*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fileStat (char const*,struct stat*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fwrite (char const*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ mkdir (char const*,int) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ symlink (char const*,char const*) ; 
 void* time (int /*<<< orphan*/ ) ; 
 scalar_t__ utimensat (int /*<<< orphan*/ ,char const*,struct timespec*,int /*<<< orphan*/ ) ; 
 scalar_t__ utimes (char const*,struct timeval*) ; 

__attribute__((used)) static int writeFile(
  sqlite3_context *pCtx,          /* Context to return bytes written in */
  const char *zFile,              /* File to write */
  sqlite3_value *pData,           /* Data to write */
  mode_t mode,                    /* MODE parameter passed to writefile() */
  sqlite3_int64 mtime             /* MTIME parameter (or -1 to not set time) */
){
#if !defined(_WIN32) && !defined(WIN32)
  if( S_ISLNK(mode) ){
    const char *zTo = (const char*)sqlite3_value_text(pData);
    if( symlink(zTo, zFile)<0 ) return 1;
  }else
#endif
  {
    if( S_ISDIR(mode) ){
      if( mkdir(zFile, mode) ){
        /* The mkdir() call to create the directory failed. This might not
        ** be an error though - if there is already a directory at the same
        ** path and either the permissions already match or can be changed
        ** to do so using chmod(), it is not an error.  */
        struct stat sStat;
        if( errno!=EEXIST
         || 0!=fileStat(zFile, &sStat)
         || !S_ISDIR(sStat.st_mode)
         || ((sStat.st_mode&0777)!=(mode&0777) && 0!=chmod(zFile, mode&0777))
        ){
          return 1;
        }
      }
    }else{
      sqlite3_int64 nWrite = 0;
      const char *z;
      int rc = 0;
      FILE *out = fopen(zFile, "wb");
      if( out==0 ) return 1;
      z = (const char*)sqlite3_value_blob(pData);
      if( z ){
        sqlite3_int64 n = fwrite(z, 1, sqlite3_value_bytes(pData), out);
        nWrite = sqlite3_value_bytes(pData);
        if( nWrite!=n ){
          rc = 1;
        }
      }
      fclose(out);
      if( rc==0 && mode && chmod(zFile, mode & 0777) ){
        rc = 1;
      }
      if( rc ) return 2;
      sqlite3_result_int64(pCtx, nWrite);
    }
  }

  if( mtime>=0 ){
#if defined(_WIN32)
    /* Windows */
    FILETIME lastAccess;
    FILETIME lastWrite;
    SYSTEMTIME currentTime;
    LONGLONG intervals;
    HANDLE hFile;
    LPWSTR zUnicodeName;
    extern LPWSTR sqlite3_win32_utf8_to_unicode(const char*);

    GetSystemTime(&currentTime);
    SystemTimeToFileTime(&currentTime, &lastAccess);
    intervals = Int32x32To64(mtime, 10000000) + 116444736000000000;
    lastWrite.dwLowDateTime = (DWORD)intervals;
    lastWrite.dwHighDateTime = intervals >> 32;
    zUnicodeName = sqlite3_win32_utf8_to_unicode(zFile);
    if( zUnicodeName==0 ){
      return 1;
    }
    hFile = CreateFileW(
      zUnicodeName, FILE_WRITE_ATTRIBUTES, 0, NULL, OPEN_EXISTING,
      FILE_FLAG_BACKUP_SEMANTICS, NULL
    );
    sqlite3_free(zUnicodeName);
    if( hFile!=INVALID_HANDLE_VALUE ){
      BOOL bResult = SetFileTime(hFile, NULL, &lastAccess, &lastWrite);
      CloseHandle(hFile);
      return !bResult;
    }else{
      return 1;
    }
#elif defined(AT_FDCWD) && 0 /* utimensat() is not universally available */
    /* Recent unix */
    struct timespec times[2];
    times[0].tv_nsec = times[1].tv_nsec = 0;
    times[0].tv_sec = time(0);
    times[1].tv_sec = mtime;
    if( utimensat(AT_FDCWD, zFile, times, AT_SYMLINK_NOFOLLOW) ){
      return 1;
    }
#else
    /* Legacy unix */
    struct timeval times[2];
    times[0].tv_usec = times[1].tv_usec = 0;
    times[0].tv_sec = time(0);
    times[1].tv_sec = mtime;
    if( utimes(zFile, times) ){
      return 1;
    }
#endif
  }

  return 0;
}