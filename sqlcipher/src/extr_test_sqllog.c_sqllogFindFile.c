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
typedef  int /*<<< orphan*/  zLine ;
typedef  int /*<<< orphan*/  zBuf ;
struct TYPE_2__ {int /*<<< orphan*/  zPrefix; int /*<<< orphan*/  zIdx; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_IOERR ; 
 int SQLLOG_NAMESZ ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sqllog_isspace (char) ; 
 TYPE_1__ sqllogglobal ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *sqllogFindFile(const char *zFile){
  char *zRet = 0;
  FILE *fd = 0;

  /* Open the index file for reading */
  fd = fopen(sqllogglobal.zIdx, "r");
  if( fd==0 ){
    sqlite3_log(SQLITE_IOERR, "sqllogFindFile(): error in fopen()");
    return 0;
  }

  /* Loop through each entry in the index file. If zFile is not NULL and the
  ** entry is a match, then set zRet to point to the filename of the existing
  ** copy and break out of the loop.  */
  while( feof(fd)==0 ){
    char zLine[SQLLOG_NAMESZ*2+5];
    if( fgets(zLine, sizeof(zLine), fd) ){
      int n;
      char *z;

      zLine[sizeof(zLine)-1] = '\0';
      z = zLine;
      while( *z>='0' && *z<='9' ) z++;
      while( *z==' ' ) z++;

      n = strlen(z);
      while( n>0 && sqllog_isspace(z[n-1]) ) n--;

      if( n==strlen(zFile) && 0==memcmp(zFile, z, n) ){
        char zBuf[16];
        memset(zBuf, 0, sizeof(zBuf));
        z = zLine;
        while( *z>='0' && *z<='9' ){
          zBuf[z-zLine] = *z;
          z++;
        }
        zRet = sqlite3_mprintf("%s_%s.db", sqllogglobal.zPrefix, zBuf);
        break;
      }
    }
  }

  if( ferror(fd) ){
    sqlite3_log(SQLITE_IOERR, "sqllogFindFile(): error reading index file");
  }

  fclose(fd);
  return zRet;
}