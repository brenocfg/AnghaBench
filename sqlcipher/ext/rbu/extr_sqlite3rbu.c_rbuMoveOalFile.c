#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ eStage; scalar_t__ rc; scalar_t__ zErrmsg; scalar_t__ dbRbu; scalar_t__ dbMain; int /*<<< orphan*/  objiter; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  char* LPWSTR ;

/* Variables and functions */
 scalar_t__ MoveFileW (char*,char*) ; 
 scalar_t__ RBU_STAGE_MOVE ; 
 scalar_t__ SQLITE_IOERR ; 
 void* SQLITE_IOERR_NOMEM ; 
 scalar_t__ SQLITE_NOMEM ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  rbuFileSuffix3 (char const*,char*) ; 
 scalar_t__ rbuIsVacuum (TYPE_1__*) ; 
 int /*<<< orphan*/  rbuLockDatabase (TYPE_1__*) ; 
 int /*<<< orphan*/  rbuObjIterFinalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbuOpenDatabase (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbuSetupCheckpoint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* rbuWinUtf8ToUnicode (char*) ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  sqlite3_close (scalar_t__) ; 
 char* sqlite3_db_filename (scalar_t__,char*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 

__attribute__((used)) static void rbuMoveOalFile(sqlite3rbu *p){
  const char *zBase = sqlite3_db_filename(p->dbMain, "main");
  const char *zMove = zBase;
  char *zOal;
  char *zWal;

  if( rbuIsVacuum(p) ){
    zMove = sqlite3_db_filename(p->dbRbu, "main");
  }
  zOal = sqlite3_mprintf("%s-oal", zMove);
  zWal = sqlite3_mprintf("%s-wal", zMove);

  assert( p->eStage==RBU_STAGE_MOVE );
  assert( p->rc==SQLITE_OK && p->zErrmsg==0 );
  if( zWal==0 || zOal==0 ){
    p->rc = SQLITE_NOMEM;
  }else{
    /* Move the *-oal file to *-wal. At this point connection p->db is
    ** holding a SHARED lock on the target database file (because it is
    ** in WAL mode). So no other connection may be writing the db. 
    **
    ** In order to ensure that there are no database readers, an EXCLUSIVE
    ** lock is obtained here before the *-oal is moved to *-wal.
    */
    rbuLockDatabase(p);
    if( p->rc==SQLITE_OK ){
      rbuFileSuffix3(zBase, zWal);
      rbuFileSuffix3(zBase, zOal);

      /* Re-open the databases. */
      rbuObjIterFinalize(&p->objiter);
      sqlite3_close(p->dbRbu);
      sqlite3_close(p->dbMain);
      p->dbMain = 0;
      p->dbRbu = 0;

#if defined(_WIN32_WCE)
      {
        LPWSTR zWideOal;
        LPWSTR zWideWal;

        zWideOal = rbuWinUtf8ToUnicode(zOal);
        if( zWideOal ){
          zWideWal = rbuWinUtf8ToUnicode(zWal);
          if( zWideWal ){
            if( MoveFileW(zWideOal, zWideWal) ){
              p->rc = SQLITE_OK;
            }else{
              p->rc = SQLITE_IOERR;
            }
            sqlite3_free(zWideWal);
          }else{
            p->rc = SQLITE_IOERR_NOMEM;
          }
          sqlite3_free(zWideOal);
        }else{
          p->rc = SQLITE_IOERR_NOMEM;
        }
      }
#else
      p->rc = rename(zOal, zWal) ? SQLITE_IOERR : SQLITE_OK;
#endif

      if( p->rc==SQLITE_OK ){
        rbuOpenDatabase(p, 0);
        rbuSetupCheckpoint(p, 0);
      }
    }
  }

  sqlite3_free(zWal);
  sqlite3_free(zOal);
}