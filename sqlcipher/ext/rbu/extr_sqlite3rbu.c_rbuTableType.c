#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct TYPE_4__ {scalar_t__ rc; int /*<<< orphan*/  zErrmsg; int /*<<< orphan*/  dbMain; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  aStmt ;

/* Variables and functions */
 int RBU_PK_EXTERNAL ; 
 int RBU_PK_IPK ; 
 int RBU_PK_NONE ; 
 int RBU_PK_NOTABLE ; 
 int RBU_PK_VTAB ; 
 int RBU_PK_WITHOUT_ROWID ; 
 scalar_t__ SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 void* prepareFreeAndCollectError (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbuFinalize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 char* sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,char const*) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbuTableType(
  sqlite3rbu *p,
  const char *zTab,
  int *peType,
  int *piTnum,
  int *piPk
){
  /*
  ** 0) SELECT count(*) FROM sqlite_master where name=%Q AND IsVirtual(%Q)
  ** 1) PRAGMA index_list = ?
  ** 2) SELECT count(*) FROM sqlite_master where name=%Q 
  ** 3) PRAGMA table_info = ?
  */
  sqlite3_stmt *aStmt[4] = {0, 0, 0, 0};

  *peType = RBU_PK_NOTABLE;
  *piPk = 0;

  assert( p->rc==SQLITE_OK );
  p->rc = prepareFreeAndCollectError(p->dbMain, &aStmt[0], &p->zErrmsg, 
    sqlite3_mprintf(
          "SELECT (sql LIKE 'create virtual%%'), rootpage"
          "  FROM sqlite_master"
          " WHERE name=%Q", zTab
  ));
  if( p->rc!=SQLITE_OK || sqlite3_step(aStmt[0])!=SQLITE_ROW ){
    /* Either an error, or no such table. */
    goto rbuTableType_end;
  }
  if( sqlite3_column_int(aStmt[0], 0) ){
    *peType = RBU_PK_VTAB;                     /* virtual table */
    goto rbuTableType_end;
  }
  *piTnum = sqlite3_column_int(aStmt[0], 1);

  p->rc = prepareFreeAndCollectError(p->dbMain, &aStmt[1], &p->zErrmsg, 
    sqlite3_mprintf("PRAGMA index_list=%Q",zTab)
  );
  if( p->rc ) goto rbuTableType_end;
  while( sqlite3_step(aStmt[1])==SQLITE_ROW ){
    const u8 *zOrig = sqlite3_column_text(aStmt[1], 3);
    const u8 *zIdx = sqlite3_column_text(aStmt[1], 1);
    if( zOrig && zIdx && zOrig[0]=='p' ){
      p->rc = prepareFreeAndCollectError(p->dbMain, &aStmt[2], &p->zErrmsg, 
          sqlite3_mprintf(
            "SELECT rootpage FROM sqlite_master WHERE name = %Q", zIdx
      ));
      if( p->rc==SQLITE_OK ){
        if( sqlite3_step(aStmt[2])==SQLITE_ROW ){
          *piPk = sqlite3_column_int(aStmt[2], 0);
          *peType = RBU_PK_EXTERNAL;
        }else{
          *peType = RBU_PK_WITHOUT_ROWID;
        }
      }
      goto rbuTableType_end;
    }
  }

  p->rc = prepareFreeAndCollectError(p->dbMain, &aStmt[3], &p->zErrmsg, 
    sqlite3_mprintf("PRAGMA table_info=%Q",zTab)
  );
  if( p->rc==SQLITE_OK ){
    while( sqlite3_step(aStmt[3])==SQLITE_ROW ){
      if( sqlite3_column_int(aStmt[3],5)>0 ){
        *peType = RBU_PK_IPK;                /* explicit IPK column */
        goto rbuTableType_end;
      }
    }
    *peType = RBU_PK_NONE;
  }

rbuTableType_end: {
    unsigned int i;
    for(i=0; i<sizeof(aStmt)/sizeof(aStmt[0]); i++){
      rbuFinalize(p, aStmt[i]);
    }
  }
}