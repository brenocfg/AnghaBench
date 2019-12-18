#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct Db {TYPE_4__* pSchema; scalar_t__ pBt; } ;
struct TYPE_27__ {TYPE_3__* pStart; scalar_t__ bMalloced; } ;
struct TYPE_26__ {TYPE_3__* zAuthPW; TYPE_3__* zAuthUser; } ;
struct TYPE_28__ {scalar_t__ magic; int nDb; TYPE_2__ lookaside; int /*<<< orphan*/  mutex; struct Db* aDb; TYPE_1__ auth; int /*<<< orphan*/  pErr; int /*<<< orphan*/  aModule; int /*<<< orphan*/  aCollSeq; int /*<<< orphan*/  aFunc; struct Db* aDbStatic; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_29__ {int /*<<< orphan*/  pAux; int /*<<< orphan*/  (* xDestroy ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  pUser; int /*<<< orphan*/  (* xDel ) (int /*<<< orphan*/ ) ;struct TYPE_29__* pNext; } ;
typedef  TYPE_4__ Module ;
typedef  int /*<<< orphan*/  HashElem ;
typedef  TYPE_4__ FuncDef ;
typedef  TYPE_4__ CollSeq ;

/* Variables and functions */
 scalar_t__ SQLITE_MAGIC_CLOSED ; 
 scalar_t__ SQLITE_MAGIC_ERROR ; 
 scalar_t__ SQLITE_MAGIC_ZOMBIE ; 
 int /*<<< orphan*/  SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ connectionIsBusy (TYPE_3__*) ; 
 int /*<<< orphan*/  functionDestroy (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3BtreeClose (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3CloseExtensions (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3CloseSavepoints (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3CollapseDatabaseArray (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ConnectionClosed (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3HashClear (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3LookasideUsed (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3RollbackAll (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SchemaClear (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3ValueFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VtabEponymousTableClear (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3VtabUnlockList (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 TYPE_4__* sqliteHashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void sqlite3LeaveMutexAndCloseZombie(sqlite3 *db){
  HashElem *i;                    /* Hash table iterator */
  int j;

  /* If there are outstanding sqlite3_stmt or sqlite3_backup objects
  ** or if the connection has not yet been closed by sqlite3_close_v2(),
  ** then just leave the mutex and return.
  */
  if( db->magic!=SQLITE_MAGIC_ZOMBIE || connectionIsBusy(db) ){
    sqlite3_mutex_leave(db->mutex);
    return;
  }

  /* If we reach this point, it means that the database connection has
  ** closed all sqlite3_stmt and sqlite3_backup objects and has been
  ** passed to sqlite3_close (meaning that it is a zombie).  Therefore,
  ** go ahead and free all resources.
  */

  /* If a transaction is open, roll it back. This also ensures that if
  ** any database schemas have been modified by an uncommitted transaction
  ** they are reset. And that the required b-tree mutex is held to make
  ** the pager rollback and schema reset an atomic operation. */
  sqlite3RollbackAll(db, SQLITE_OK);

  /* Free any outstanding Savepoint structures. */
  sqlite3CloseSavepoints(db);

  /* Close all database connections */
  for(j=0; j<db->nDb; j++){
    struct Db *pDb = &db->aDb[j];
    if( pDb->pBt ){
      sqlite3BtreeClose(pDb->pBt);
      pDb->pBt = 0;
      if( j!=1 ){
        pDb->pSchema = 0;
      }
    }
  }
  /* Clear the TEMP schema separately and last */
  if( db->aDb[1].pSchema ){
    sqlite3SchemaClear(db->aDb[1].pSchema);
  }
  sqlite3VtabUnlockList(db);

  /* Free up the array of auxiliary databases */
  sqlite3CollapseDatabaseArray(db);
  assert( db->nDb<=2 );
  assert( db->aDb==db->aDbStatic );

  /* Tell the code in notify.c that the connection no longer holds any
  ** locks and does not require any further unlock-notify callbacks.
  */
  sqlite3ConnectionClosed(db);

  for(i=sqliteHashFirst(&db->aFunc); i; i=sqliteHashNext(i)){
    FuncDef *pNext, *p;
    p = sqliteHashData(i);
    do{
      functionDestroy(db, p);
      pNext = p->pNext;
      sqlite3DbFree(db, p);
      p = pNext;
    }while( p );
  }
  sqlite3HashClear(&db->aFunc);
  for(i=sqliteHashFirst(&db->aCollSeq); i; i=sqliteHashNext(i)){
    CollSeq *pColl = (CollSeq *)sqliteHashData(i);
    /* Invoke any destructors registered for collation sequence user data. */
    for(j=0; j<3; j++){
      if( pColl[j].xDel ){
        pColl[j].xDel(pColl[j].pUser);
      }
    }
    sqlite3DbFree(db, pColl);
  }
  sqlite3HashClear(&db->aCollSeq);
#ifndef SQLITE_OMIT_VIRTUALTABLE
  for(i=sqliteHashFirst(&db->aModule); i; i=sqliteHashNext(i)){
    Module *pMod = (Module *)sqliteHashData(i);
    if( pMod->xDestroy ){
      pMod->xDestroy(pMod->pAux);
    }
    sqlite3VtabEponymousTableClear(db, pMod);
    sqlite3DbFree(db, pMod);
  }
  sqlite3HashClear(&db->aModule);
#endif

  sqlite3Error(db, SQLITE_OK); /* Deallocates any cached error strings. */
  sqlite3ValueFree(db->pErr);
  sqlite3CloseExtensions(db);
#if SQLITE_USER_AUTHENTICATION
  sqlite3_free(db->auth.zAuthUser);
  sqlite3_free(db->auth.zAuthPW);
#endif

  db->magic = SQLITE_MAGIC_ERROR;

  /* The temp-database schema is allocated differently from the other schema
  ** objects (using sqliteMalloc() directly, instead of sqlite3BtreeSchema()).
  ** So it needs to be freed here. Todo: Why not roll the temp schema into
  ** the same sqliteMalloc() as the one that allocates the database 
  ** structure?
  */
  sqlite3DbFree(db, db->aDb[1].pSchema);
  sqlite3_mutex_leave(db->mutex);
  db->magic = SQLITE_MAGIC_CLOSED;
  sqlite3_mutex_free(db->mutex);
  assert( sqlite3LookasideUsed(db,0)==0 );
  if( db->lookaside.bMalloced ){
    sqlite3_free(db->lookaside.pStart);
  }
  sqlite3_free(db);
}