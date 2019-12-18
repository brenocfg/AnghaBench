#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {TYPE_2__* aDb; scalar_t__ mallocFailed; } ;
typedef  TYPE_3__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_29__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_4__ Table ;
struct TYPE_32__ {scalar_t__ idxType; char const* zName; int /*<<< orphan*/  tnum; TYPE_4__* pTable; int /*<<< orphan*/  pSchema; } ;
struct TYPE_31__ {scalar_t__ nErr; int checkSchema; TYPE_3__* db; } ;
struct TYPE_30__ {int nSrc; TYPE_1__* a; } ;
struct TYPE_27__ {char* zDbSName; } ;
struct TYPE_26__ {int /*<<< orphan*/  zDatabase; int /*<<< orphan*/  zName; } ;
typedef  TYPE_5__ SrcList ;
typedef  TYPE_6__ Parse ;
typedef  TYPE_7__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  MASTER_NAME ; 
 int /*<<< orphan*/  OMIT_TEMPDB ; 
 int /*<<< orphan*/  OP_DropIndex ; 
 char* SCHEMA_TABLE (int) ; 
 int SQLITE_DELETE ; 
 int SQLITE_DROP_INDEX ; 
 int SQLITE_DROP_TEMP_INDEX ; 
 scalar_t__ SQLITE_IDXTYPE_APPDEF ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  destroyRootPage (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3AuthCheck (TYPE_6__*,int,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sqlite3BeginWriteOperation (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ChangeCookie (TYPE_6__*,int) ; 
 int /*<<< orphan*/  sqlite3ClearStatTables (TYPE_6__*,int,char*,char const*) ; 
 int /*<<< orphan*/  sqlite3CodeVerifyNamedSchema (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_6__*,char*,TYPE_5__*,...) ; 
 TYPE_7__* sqlite3FindIndex (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3NestedParse (TYPE_6__*,char*,char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ sqlite3ReadSchema (TYPE_6__*) ; 
 int sqlite3SchemaToIndex (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListDelete (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void sqlite3DropIndex(Parse *pParse, SrcList *pName, int ifExists){
  Index *pIndex;
  Vdbe *v;
  sqlite3 *db = pParse->db;
  int iDb;

  assert( pParse->nErr==0 );   /* Never called with prior errors */
  if( db->mallocFailed ){
    goto exit_drop_index;
  }
  assert( pName->nSrc==1 );
  if( SQLITE_OK!=sqlite3ReadSchema(pParse) ){
    goto exit_drop_index;
  }
  pIndex = sqlite3FindIndex(db, pName->a[0].zName, pName->a[0].zDatabase);
  if( pIndex==0 ){
    if( !ifExists ){
      sqlite3ErrorMsg(pParse, "no such index: %S", pName, 0);
    }else{
      sqlite3CodeVerifyNamedSchema(pParse, pName->a[0].zDatabase);
    }
    pParse->checkSchema = 1;
    goto exit_drop_index;
  }
  if( pIndex->idxType!=SQLITE_IDXTYPE_APPDEF ){
    sqlite3ErrorMsg(pParse, "index associated with UNIQUE "
      "or PRIMARY KEY constraint cannot be dropped", 0);
    goto exit_drop_index;
  }
  iDb = sqlite3SchemaToIndex(db, pIndex->pSchema);
#ifndef SQLITE_OMIT_AUTHORIZATION
  {
    int code = SQLITE_DROP_INDEX;
    Table *pTab = pIndex->pTable;
    const char *zDb = db->aDb[iDb].zDbSName;
    const char *zTab = SCHEMA_TABLE(iDb);
    if( sqlite3AuthCheck(pParse, SQLITE_DELETE, zTab, 0, zDb) ){
      goto exit_drop_index;
    }
    if( !OMIT_TEMPDB && iDb ) code = SQLITE_DROP_TEMP_INDEX;
    if( sqlite3AuthCheck(pParse, code, pIndex->zName, pTab->zName, zDb) ){
      goto exit_drop_index;
    }
  }
#endif

  /* Generate code to remove the index and from the master table */
  v = sqlite3GetVdbe(pParse);
  if( v ){
    sqlite3BeginWriteOperation(pParse, 1, iDb);
    sqlite3NestedParse(pParse,
       "DELETE FROM %Q.%s WHERE name=%Q AND type='index'",
       db->aDb[iDb].zDbSName, MASTER_NAME, pIndex->zName
    );
    sqlite3ClearStatTables(pParse, iDb, "idx", pIndex->zName);
    sqlite3ChangeCookie(pParse, iDb);
    destroyRootPage(pParse, pIndex->tnum, iDb);
    sqlite3VdbeAddOp4(v, OP_DropIndex, iDb, 0, 0, pIndex->zName, 0);
  }

exit_drop_index:
  sqlite3SrcListDelete(db, pName);
}