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
struct SLConn {scalar_t__ fd; int /*<<< orphan*/ * db; scalar_t__ iLog; } ;
typedef  int /*<<< orphan*/  sqlite3_mutex ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_2__ {scalar_t__ bRec; int nConn; int /*<<< orphan*/ * mutex; struct SLConn* aConn; int /*<<< orphan*/  iNextLog; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  SQLITE_MUTEX_STATIC_MASTER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  memmove (struct SLConn*,struct SLConn*,int) ; 
 void* sqlite3_mutex_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqllogCopydb (struct SLConn*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqllogOpenlog (struct SLConn*) ; 
 scalar_t__ sqllogTraceDb (int /*<<< orphan*/ *) ; 
 TYPE_1__ sqllogglobal ; 
 int /*<<< orphan*/  testSqllogStmt (struct SLConn*,char const*) ; 

__attribute__((used)) static void testSqllog(void *pCtx, sqlite3 *db, const char *zSql, int eType){
  struct SLConn *p = 0;
  sqlite3_mutex *master = sqlite3_mutex_alloc(SQLITE_MUTEX_STATIC_MASTER);

  assert( eType==0 || eType==1 || eType==2 );
  assert( (eType==2)==(zSql==0) );

  /* This is a database open command. */
  if( eType==0 ){
    sqlite3_mutex_enter(master);
    if( sqllogglobal.mutex==0 ){
      sqllogglobal.mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_RECURSIVE);
    }
    sqlite3_mutex_leave(master);

    sqlite3_mutex_enter(sqllogglobal.mutex);
    if( sqllogglobal.bRec==0 && sqllogTraceDb(db) ){

      sqlite3_mutex_enter(master);
      p = &sqllogglobal.aConn[sqllogglobal.nConn++];
      p->fd = 0;
      p->db = db;
      p->iLog = sqllogglobal.iNextLog++;
      sqlite3_mutex_leave(master);

      /* Open the log and take a copy of the main database file */
      sqllogOpenlog(p);
      if( p->fd ) sqllogCopydb(p, "main", 0);
    }
    sqlite3_mutex_leave(sqllogglobal.mutex);
  }

  else{

    int i;
    for(i=0; i<sqllogglobal.nConn; i++){
      p = &sqllogglobal.aConn[i];
      if( p->db==db ) break;
    }

    /* A database handle close command */
    if( eType==2 ){
      sqlite3_mutex_enter(master);
      if( i<sqllogglobal.nConn ){
        if( p->fd ) fclose(p->fd);
        p->db = 0;
        p->fd = 0;
        sqllogglobal.nConn--;
      }

      if( sqllogglobal.nConn==0 ){
        sqlite3_mutex_free(sqllogglobal.mutex);
        sqllogglobal.mutex = 0;
      }else if( i<sqllogglobal.nConn ){
        int nShift = &sqllogglobal.aConn[sqllogglobal.nConn] - p;
        if( nShift>0 ){
          memmove(p, &p[1], nShift*sizeof(struct SLConn));
        }
      }
      sqlite3_mutex_leave(master);

    /* An ordinary SQL command. */
    }else if( i<sqllogglobal.nConn && p->fd ){
      sqlite3_mutex_enter(sqllogglobal.mutex);
      if( sqllogglobal.bRec==0 ){
        testSqllogStmt(p, zSql);
      }
      sqlite3_mutex_leave(sqllogglobal.mutex);
    }
  }
}