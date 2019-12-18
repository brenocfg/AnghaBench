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
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_2__ {int nAlloc; char* zBuf; int nBuf; int /*<<< orphan*/  pStmt; } ;
typedef  TYPE_1__ fs_cursor ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int SQLITE_ERROR ; 
 int SQLITE_IOERR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 
 char* sqlite3Realloc (char*,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_column_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsColumn(sqlite3_vtab_cursor *cur, sqlite3_context *ctx, int i){
  fs_cursor *pCur = (fs_cursor*)cur;

  assert( i==0 || i==1 || i==2 );
  if( i==0 ){
    sqlite3_result_value(ctx, sqlite3_column_value(pCur->pStmt, 0));
  }else{
    const char *zFile = (const char *)sqlite3_column_text(pCur->pStmt, 1);
    struct stat sbuf;
    int fd;

    int n;
    fd = open(zFile, O_RDONLY);
    if( fd<0 ) return SQLITE_IOERR;
    fstat(fd, &sbuf);

    if( sbuf.st_size>=pCur->nAlloc ){
      sqlite3_int64 nNew = sbuf.st_size*2;
      char *zNew;
      if( nNew<1024 ) nNew = 1024;

      zNew = sqlite3Realloc(pCur->zBuf, nNew);
      if( zNew==0 ){
        close(fd);
        return SQLITE_NOMEM;
      }
      pCur->zBuf = zNew;
      pCur->nAlloc = nNew;
    }

    n = (int)read(fd, pCur->zBuf, sbuf.st_size);
    close(fd);
    if( n!=sbuf.st_size ) return SQLITE_ERROR;
    pCur->nBuf = sbuf.st_size;
    pCur->zBuf[pCur->nBuf] = '\0';

    sqlite3_result_text(ctx, pCur->zBuf, -1, SQLITE_TRANSIENT);
  }
  return SQLITE_OK;
}