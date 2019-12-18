#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_27__ {scalar_t__ z; } ;
typedef  TYPE_3__ Token ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_28__ {TYPE_2__* db; } ;
struct TYPE_25__ {char* zDbSName; } ;
typedef  TYPE_4__ Parse ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  ENC (TYPE_2__*) ; 
 scalar_t__ NEVER (int) ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  reindexDatabases (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  reindexTable (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BeginWriteOperation (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_4__*,char*) ; 
 int /*<<< orphan*/ * sqlite3FindCollSeq (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3FindIndex (TYPE_2__*,char*,char const*) ; 
 int /*<<< orphan*/ * sqlite3FindTable (TYPE_2__*,char*,char const*) ; 
 char* sqlite3NameFromToken (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ sqlite3ReadSchema (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3RefillIndex (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int sqlite3TwoPartName (TYPE_4__*,TYPE_3__*,TYPE_3__*,TYPE_3__**) ; 

void sqlite3Reindex(Parse *pParse, Token *pName1, Token *pName2){
  CollSeq *pColl;             /* Collating sequence to be reindexed, or NULL */
  char *z;                    /* Name of a table or index */
  const char *zDb;            /* Name of the database */
  Table *pTab;                /* A table in the database */
  Index *pIndex;              /* An index associated with pTab */
  int iDb;                    /* The database index number */
  sqlite3 *db = pParse->db;   /* The database connection */
  Token *pObjName;            /* Name of the table or index to be reindexed */

  /* Read the database schema. If an error occurs, leave an error message
  ** and code in pParse and return NULL. */
  if( SQLITE_OK!=sqlite3ReadSchema(pParse) ){
    return;
  }

  if( pName1==0 ){
    reindexDatabases(pParse, 0);
    return;
  }else if( NEVER(pName2==0) || pName2->z==0 ){
    char *zColl;
    assert( pName1->z );
    zColl = sqlite3NameFromToken(pParse->db, pName1);
    if( !zColl ) return;
    pColl = sqlite3FindCollSeq(db, ENC(db), zColl, 0);
    if( pColl ){
      reindexDatabases(pParse, zColl);
      sqlite3DbFree(db, zColl);
      return;
    }
    sqlite3DbFree(db, zColl);
  }
  iDb = sqlite3TwoPartName(pParse, pName1, pName2, &pObjName);
  if( iDb<0 ) return;
  z = sqlite3NameFromToken(db, pObjName);
  if( z==0 ) return;
  zDb = db->aDb[iDb].zDbSName;
  pTab = sqlite3FindTable(db, z, zDb);
  if( pTab ){
    reindexTable(pParse, pTab, 0);
    sqlite3DbFree(db, z);
    return;
  }
  pIndex = sqlite3FindIndex(db, z, zDb);
  sqlite3DbFree(db, z);
  if( pIndex ){
    sqlite3BeginWriteOperation(pParse, 0, iDb);
    sqlite3RefillIndex(pParse, pIndex, -1);
    return;
  }
  sqlite3ErrorMsg(pParse, "unable to identify the object to be reindexed");
}