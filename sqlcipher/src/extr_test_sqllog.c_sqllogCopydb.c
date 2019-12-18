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
struct SLConn {int /*<<< orphan*/  fd; int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  sqlite3_backup ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_2__ {int bRec; int /*<<< orphan*/  iClock; int /*<<< orphan*/  zIdx; int /*<<< orphan*/  zPrefix; int /*<<< orphan*/  iNextDb; scalar_t__ bReuse; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLLOG_NAMESZ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int sqlite3_backup_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_backup_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlite3_backup_step (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 int sqlite3_errcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_log (int,char*) ; 
 char* sqlite3_mprintf (char*,...) ; 
 int sqlite3_open (char*,int /*<<< orphan*/ **) ; 
 int sqllogFindAttached (int /*<<< orphan*/ ,char const*,char*,char*) ; 
 char* sqllogFindFile (char*) ; 
 TYPE_1__ sqllogglobal ; 

__attribute__((used)) static void sqllogCopydb(struct SLConn *p, const char *zSearch, int bLog){
  char zName[SQLLOG_NAMESZ];      /* Attached database name */
  char zFile[SQLLOG_NAMESZ];      /* Database file name */
  char *zFree;
  char *zInit = 0;
  int rc;

  rc = sqllogFindAttached(p->db, zSearch, zName, zFile);
  if( rc!=SQLITE_OK ) return;

  if( zFile[0]=='\0' ){
    zInit = sqlite3_mprintf("");
  }else{
    if( sqllogglobal.bReuse ){
      zInit = sqllogFindFile(zFile);
    }else{
      zInit = 0;
    }
    if( zInit==0 ){
      int rc;
      sqlite3 *copy = 0;
      int iDb;

      /* Generate a file-name to use for the copy of this database */
      iDb = sqllogglobal.iNextDb++;
      zInit = sqlite3_mprintf("%s_%02d.db", sqllogglobal.zPrefix, iDb);

      /* Create the backup */
      assert( sqllogglobal.bRec==0 );
      sqllogglobal.bRec = 1;
      rc = sqlite3_open(zInit, &copy);
      if( rc==SQLITE_OK ){
        sqlite3_backup *pBak;
        sqlite3_exec(copy, "PRAGMA synchronous = 0", 0, 0, 0);
        pBak = sqlite3_backup_init(copy, "main", p->db, zName);
        if( pBak ){
          sqlite3_backup_step(pBak, -1);
          rc = sqlite3_backup_finish(pBak);
        }else{
          rc = sqlite3_errcode(copy);
        }
        sqlite3_close(copy);
      }
      sqllogglobal.bRec = 0;

      if( rc==SQLITE_OK ){
        /* Write an entry into the database index file */
        FILE *fd = fopen(sqllogglobal.zIdx, "a");
        if( fd ){
          fprintf(fd, "%d %s\n", iDb, zFile);
          fclose(fd);
        }
      }else{
        sqlite3_log(rc, "sqllogCopydb(): error backing up database");
      }
    }
  }

  if( bLog ){
    zFree = sqlite3_mprintf("ATTACH '%q' AS '%q'; -- clock=%d\n", 
        zInit, zName, sqllogglobal.iClock++
    );
  }else{
    zFree = sqlite3_mprintf("-- Main database is '%q'\n", zInit);
  }
  fprintf(p->fd, "%s", zFree);
  sqlite3_free(zFree);

  sqlite3_free(zInit);
}