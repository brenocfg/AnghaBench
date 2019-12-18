#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int nDb; scalar_t__ nSqlExec; TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_29__ {scalar_t__ n; } ;
typedef  TYPE_3__ Token ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_31__ {int /*<<< orphan*/ * pTable; } ;
struct TYPE_30__ {TYPE_2__* db; } ;
struct TYPE_27__ {char* zDbSName; } ;
typedef  TYPE_4__ Parse ;
typedef  TYPE_5__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Expire ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  analyzeDatabase (TYPE_4__*,int) ; 
 int /*<<< orphan*/  analyzeTable (TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3BtreeHoldsAllMutexes (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_2__*,char*) ; 
 int sqlite3FindDb (TYPE_2__*,TYPE_3__*) ; 
 TYPE_5__* sqlite3FindIndex (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_4__*) ; 
 int /*<<< orphan*/ * sqlite3LocateTable (TYPE_4__*,int /*<<< orphan*/ ,char*,char*) ; 
 char* sqlite3NameFromToken (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ sqlite3ReadSchema (TYPE_4__*) ; 
 int sqlite3TwoPartName (TYPE_4__*,TYPE_3__*,TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3Analyze(Parse *pParse, Token *pName1, Token *pName2){
  sqlite3 *db = pParse->db;
  int iDb;
  int i;
  char *z, *zDb;
  Table *pTab;
  Index *pIdx;
  Token *pTableName;
  Vdbe *v;

  /* Read the database schema. If an error occurs, leave an error message
  ** and code in pParse and return NULL. */
  assert( sqlite3BtreeHoldsAllMutexes(pParse->db) );
  if( SQLITE_OK!=sqlite3ReadSchema(pParse) ){
    return;
  }

  assert( pName2!=0 || pName1==0 );
  if( pName1==0 ){
    /* Form 1:  Analyze everything */
    for(i=0; i<db->nDb; i++){
      if( i==1 ) continue;  /* Do not analyze the TEMP database */
      analyzeDatabase(pParse, i);
    }
  }else if( pName2->n==0 && (iDb = sqlite3FindDb(db, pName1))>=0 ){
    /* Analyze the schema named as the argument */
    analyzeDatabase(pParse, iDb);
  }else{
    /* Form 3: Analyze the table or index named as an argument */
    iDb = sqlite3TwoPartName(pParse, pName1, pName2, &pTableName);
    if( iDb>=0 ){
      zDb = pName2->n ? db->aDb[iDb].zDbSName : 0;
      z = sqlite3NameFromToken(db, pTableName);
      if( z ){
        if( (pIdx = sqlite3FindIndex(db, z, zDb))!=0 ){
          analyzeTable(pParse, pIdx->pTable, pIdx);
        }else if( (pTab = sqlite3LocateTable(pParse, 0, z, zDb))!=0 ){
          analyzeTable(pParse, pTab, 0);
        }
        sqlite3DbFree(db, z);
      }
    }
  }
  if( db->nSqlExec==0 && (v = sqlite3GetVdbe(pParse))!=0 ){
    sqlite3VdbeAddOp0(v, OP_Expire);
  }
}