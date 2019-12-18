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
struct stat {int st_mode; int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  pStmt; } ;
typedef  TYPE_1__ FstreeCsr ;

/* Variables and functions */
 int SQLITE_IOERR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 scalar_t__ S_ISREG (int) ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sqlite3_column_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc (int) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fstreeColumn(sqlite3_vtab_cursor *cur, sqlite3_context *ctx, int i){
  FstreeCsr *pCsr = (FstreeCsr*)cur;
  if( i==0 ){      /* path */
    sqlite3_result_value(ctx, sqlite3_column_value(pCsr->pStmt, 0));
  }else{
    struct stat sBuf;
    fstat(pCsr->fd, &sBuf);

    if( S_ISREG(sBuf.st_mode) ){
      if( i==1 ){
        sqlite3_result_int64(ctx, sBuf.st_size);
      }else{
        int nRead;
        char *aBuf = sqlite3_malloc(sBuf.st_mode+1);
        if( !aBuf ) return SQLITE_NOMEM;
        nRead = read(pCsr->fd, aBuf, sBuf.st_mode);
        if( nRead!=sBuf.st_mode ){
          return SQLITE_IOERR;
        }
        sqlite3_result_blob(ctx, aBuf, nRead, SQLITE_TRANSIENT);
        sqlite3_free(aBuf);
      }
    }
  }

  return SQLITE_OK;
}