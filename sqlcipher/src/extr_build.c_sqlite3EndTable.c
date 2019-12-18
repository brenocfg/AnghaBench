#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_56__   TYPE_9__ ;
typedef  struct TYPE_55__   TYPE_8__ ;
typedef  struct TYPE_54__   TYPE_7__ ;
typedef  struct TYPE_53__   TYPE_6__ ;
typedef  struct TYPE_52__   TYPE_5__ ;
typedef  struct TYPE_51__   TYPE_4__ ;
typedef  struct TYPE_50__   TYPE_3__ ;
typedef  struct TYPE_49__   TYPE_2__ ;
typedef  struct TYPE_48__   TYPE_1__ ;
typedef  struct TYPE_47__   TYPE_11__ ;
typedef  struct TYPE_46__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_50__ {int newTnum; scalar_t__ busy; } ;
struct TYPE_51__ {int /*<<< orphan*/  mDbFlags; TYPE_3__ init; TYPE_11__* aDb; int /*<<< orphan*/  mallocFailed; } ;
typedef  TYPE_4__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_52__ {char* z; scalar_t__ n; } ;
typedef  TYPE_5__ Token ;
struct TYPE_53__ {int tabFlags; int tnum; scalar_t__ iPKey; scalar_t__ pSelect; scalar_t__ addColOffset; int /*<<< orphan*/  zName; TYPE_8__* pSchema; scalar_t__ aCol; scalar_t__ nCol; TYPE_10__* pIndex; scalar_t__ pCheck; } ;
typedef  TYPE_6__ Table ;
struct TYPE_49__ {int z; } ;
struct TYPE_56__ {int nMem; int nTab; int regRoot; TYPE_2__ sNameToken; TYPE_6__* pNewTable; int /*<<< orphan*/  regRowid; TYPE_5__ sLastToken; scalar_t__ nErr; TYPE_4__* db; } ;
struct TYPE_55__ {int /*<<< orphan*/  tblHash; } ;
struct TYPE_54__ {int iSDParm; int iSdst; int nSdst; } ;
struct TYPE_48__ {scalar_t__ pSeqTab; } ;
struct TYPE_47__ {int /*<<< orphan*/  zDbSName; TYPE_1__* pSchema; } ;
struct TYPE_46__ {struct TYPE_46__* pNext; } ;
typedef  TYPE_7__ SelectDest ;
typedef  int /*<<< orphan*/  Select ;
typedef  TYPE_8__ Schema ;
typedef  TYPE_9__ Parse ;
typedef  TYPE_10__ Index ;
typedef  TYPE_11__ Db ;

/* Variables and functions */
 int /*<<< orphan*/  DBFLAG_SchemaChange ; 
 int /*<<< orphan*/  MASTER_NAME ; 
 int /*<<< orphan*/  NC_IsCheck ; 
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  OPFLAG_P2ISREG ; 
 int /*<<< orphan*/  OP_Close ; 
 int /*<<< orphan*/  OP_InitCoroutine ; 
 int /*<<< orphan*/  OP_Insert ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_NewRowid ; 
 int /*<<< orphan*/  OP_OpenWrite ; 
 int /*<<< orphan*/  OP_Yield ; 
 int /*<<< orphan*/  SRT_Coroutine ; 
 int TF_Autoincrement ; 
 int TF_HasPrimaryKey ; 
 int TF_NoVisibleRowid ; 
 int TF_Readonly ; 
 int TF_Shadow ; 
 int TF_WithoutRowid ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  convertToWithoutRowidTable (TYPE_9__*,TYPE_6__*) ; 
 char* createTableStmt (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  estimateIndexWidth (TYPE_10__*) ; 
 int /*<<< orphan*/  estimateTableWidth (TYPE_6__*) ; 
 scalar_t__ isShadowTableName (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ChangeCookie (TYPE_9__*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  sqlite3DeleteTable (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_9__*,char*,...) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_9__*) ; 
 TYPE_6__* sqlite3HashInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*) ; 
 char* sqlite3MPrintf (TYPE_4__*,char*,char*,...) ; 
 int /*<<< orphan*/  sqlite3MayAbort (TYPE_9__*) ; 
 int /*<<< orphan*/  sqlite3NestedParse (TYPE_9__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sqlite3OomFault (TYPE_4__*) ; 
 scalar_t__ sqlite3PrimaryKeyIndex (TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3ResolveSelfReference (TYPE_9__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_6__* sqlite3ResultSetOfSelect (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int sqlite3SchemaMutexHeld (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int sqlite3SchemaToIndex (TYPE_4__*,TYPE_8__*) ; 
 int /*<<< orphan*/  sqlite3Select (TYPE_9__*,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3SelectDestInit (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3TableAffinity (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3Utf8CharLen (char const*,int) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddParseSchemaOp (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeEndCoroutine (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeGoto (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 

void sqlite3EndTable(
  Parse *pParse,          /* Parse context */
  Token *pCons,           /* The ',' token after the last column defn. */
  Token *pEnd,            /* The ')' before options in the CREATE TABLE */
  u8 tabOpts,             /* Extra table options. Usually 0. */
  Select *pSelect         /* Select from a "CREATE ... AS SELECT" */
){
  Table *p;                 /* The new table */
  sqlite3 *db = pParse->db; /* The database connection */
  int iDb;                  /* Database in which the table lives */
  Index *pIdx;              /* An implied index of the table */

  if( pEnd==0 && pSelect==0 ){
    return;
  }
  assert( !db->mallocFailed );
  p = pParse->pNewTable;
  if( p==0 ) return;

  if( pSelect==0 && isShadowTableName(db, p->zName) ){
    p->tabFlags |= TF_Shadow;
  }

  /* If the db->init.busy is 1 it means we are reading the SQL off the
  ** "sqlite_master" or "sqlite_temp_master" table on the disk.
  ** So do not write to the disk again.  Extract the root page number
  ** for the table from the db->init.newTnum field.  (The page number
  ** should have been put there by the sqliteOpenCb routine.)
  **
  ** If the root page number is 1, that means this is the sqlite_master
  ** table itself.  So mark it read-only.
  */
  if( db->init.busy ){
    if( pSelect ){
      sqlite3ErrorMsg(pParse, "");
      return;
    }
    p->tnum = db->init.newTnum;
    if( p->tnum==1 ) p->tabFlags |= TF_Readonly;
  }

  assert( (p->tabFlags & TF_HasPrimaryKey)==0
       || p->iPKey>=0 || sqlite3PrimaryKeyIndex(p)!=0 );
  assert( (p->tabFlags & TF_HasPrimaryKey)!=0
       || (p->iPKey<0 && sqlite3PrimaryKeyIndex(p)==0) );

  /* Special processing for WITHOUT ROWID Tables */
  if( tabOpts & TF_WithoutRowid ){
    if( (p->tabFlags & TF_Autoincrement) ){
      sqlite3ErrorMsg(pParse,
          "AUTOINCREMENT not allowed on WITHOUT ROWID tables");
      return;
    }
    if( (p->tabFlags & TF_HasPrimaryKey)==0 ){
      sqlite3ErrorMsg(pParse, "PRIMARY KEY missing on table %s", p->zName);
    }else{
      p->tabFlags |= TF_WithoutRowid | TF_NoVisibleRowid;
      convertToWithoutRowidTable(pParse, p);
    }
  }

  iDb = sqlite3SchemaToIndex(db, p->pSchema);

#ifndef SQLITE_OMIT_CHECK
  /* Resolve names in all CHECK constraint expressions.
  */
  if( p->pCheck ){
    sqlite3ResolveSelfReference(pParse, p, NC_IsCheck, 0, p->pCheck);
  }
#endif /* !defined(SQLITE_OMIT_CHECK) */

  /* Estimate the average row size for the table and for all implied indices */
  estimateTableWidth(p);
  for(pIdx=p->pIndex; pIdx; pIdx=pIdx->pNext){
    estimateIndexWidth(pIdx);
  }

  /* If not initializing, then create a record for the new table
  ** in the SQLITE_MASTER table of the database.
  **
  ** If this is a TEMPORARY table, write the entry into the auxiliary
  ** file instead of into the main database file.
  */
  if( !db->init.busy ){
    int n;
    Vdbe *v;
    char *zType;    /* "view" or "table" */
    char *zType2;   /* "VIEW" or "TABLE" */
    char *zStmt;    /* Text of the CREATE TABLE or CREATE VIEW statement */

    v = sqlite3GetVdbe(pParse);
    if( NEVER(v==0) ) return;

    sqlite3VdbeAddOp1(v, OP_Close, 0);

    /* 
    ** Initialize zType for the new view or table.
    */
    if( p->pSelect==0 ){
      /* A regular table */
      zType = "table";
      zType2 = "TABLE";
#ifndef SQLITE_OMIT_VIEW
    }else{
      /* A view */
      zType = "view";
      zType2 = "VIEW";
#endif
    }

    /* If this is a CREATE TABLE xx AS SELECT ..., execute the SELECT
    ** statement to populate the new table. The root-page number for the
    ** new table is in register pParse->regRoot.
    **
    ** Once the SELECT has been coded by sqlite3Select(), it is in a
    ** suitable state to query for the column names and types to be used
    ** by the new table.
    **
    ** A shared-cache write-lock is not required to write to the new table,
    ** as a schema-lock must have already been obtained to create it. Since
    ** a schema-lock excludes all other database users, the write-lock would
    ** be redundant.
    */
    if( pSelect ){
      SelectDest dest;    /* Where the SELECT should store results */
      int regYield;       /* Register holding co-routine entry-point */
      int addrTop;        /* Top of the co-routine */
      int regRec;         /* A record to be insert into the new table */
      int regRowid;       /* Rowid of the next row to insert */
      int addrInsLoop;    /* Top of the loop for inserting rows */
      Table *pSelTab;     /* A table that describes the SELECT results */

      regYield = ++pParse->nMem;
      regRec = ++pParse->nMem;
      regRowid = ++pParse->nMem;
      assert(pParse->nTab==1);
      sqlite3MayAbort(pParse);
      sqlite3VdbeAddOp3(v, OP_OpenWrite, 1, pParse->regRoot, iDb);
      sqlite3VdbeChangeP5(v, OPFLAG_P2ISREG);
      pParse->nTab = 2;
      addrTop = sqlite3VdbeCurrentAddr(v) + 1;
      sqlite3VdbeAddOp3(v, OP_InitCoroutine, regYield, 0, addrTop);
      if( pParse->nErr ) return;
      pSelTab = sqlite3ResultSetOfSelect(pParse, pSelect);
      if( pSelTab==0 ) return;
      assert( p->aCol==0 );
      p->nCol = pSelTab->nCol;
      p->aCol = pSelTab->aCol;
      pSelTab->nCol = 0;
      pSelTab->aCol = 0;
      sqlite3DeleteTable(db, pSelTab);
      sqlite3SelectDestInit(&dest, SRT_Coroutine, regYield);
      sqlite3Select(pParse, pSelect, &dest);
      if( pParse->nErr ) return;
      sqlite3VdbeEndCoroutine(v, regYield);
      sqlite3VdbeJumpHere(v, addrTop - 1);
      addrInsLoop = sqlite3VdbeAddOp1(v, OP_Yield, dest.iSDParm);
      VdbeCoverage(v);
      sqlite3VdbeAddOp3(v, OP_MakeRecord, dest.iSdst, dest.nSdst, regRec);
      sqlite3TableAffinity(v, p, 0);
      sqlite3VdbeAddOp2(v, OP_NewRowid, 1, regRowid);
      sqlite3VdbeAddOp3(v, OP_Insert, 1, regRec, regRowid);
      sqlite3VdbeGoto(v, addrInsLoop);
      sqlite3VdbeJumpHere(v, addrInsLoop);
      sqlite3VdbeAddOp1(v, OP_Close, 1);
    }

    /* Compute the complete text of the CREATE statement */
    if( pSelect ){
      zStmt = createTableStmt(db, p);
    }else{
      Token *pEnd2 = tabOpts ? &pParse->sLastToken : pEnd;
      n = (int)(pEnd2->z - pParse->sNameToken.z);
      if( pEnd2->z[0]!=';' ) n += pEnd2->n;
      zStmt = sqlite3MPrintf(db, 
          "CREATE %s %.*s", zType2, n, pParse->sNameToken.z
      );
    }

    /* A slot for the record has already been allocated in the 
    ** SQLITE_MASTER table.  We just need to update that slot with all
    ** the information we've collected.
    */
    sqlite3NestedParse(pParse,
      "UPDATE %Q.%s "
         "SET type='%s', name=%Q, tbl_name=%Q, rootpage=#%d, sql=%Q "
       "WHERE rowid=#%d",
      db->aDb[iDb].zDbSName, MASTER_NAME,
      zType,
      p->zName,
      p->zName,
      pParse->regRoot,
      zStmt,
      pParse->regRowid
    );
    sqlite3DbFree(db, zStmt);
    sqlite3ChangeCookie(pParse, iDb);

#ifndef SQLITE_OMIT_AUTOINCREMENT
    /* Check to see if we need to create an sqlite_sequence table for
    ** keeping track of autoincrement keys.
    */
    if( (p->tabFlags & TF_Autoincrement)!=0 ){
      Db *pDb = &db->aDb[iDb];
      assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
      if( pDb->pSchema->pSeqTab==0 ){
        sqlite3NestedParse(pParse,
          "CREATE TABLE %Q.sqlite_sequence(name,seq)",
          pDb->zDbSName
        );
      }
    }
#endif

    /* Reparse everything to update our internal data structures */
    sqlite3VdbeAddParseSchemaOp(v, iDb,
           sqlite3MPrintf(db, "tbl_name='%q' AND type!='trigger'", p->zName));
  }


  /* Add the table to the in-memory representation of the database.
  */
  if( db->init.busy ){
    Table *pOld;
    Schema *pSchema = p->pSchema;
    assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
    pOld = sqlite3HashInsert(&pSchema->tblHash, p->zName, p);
    if( pOld ){
      assert( p==pOld );  /* Malloc must have failed inside HashInsert() */
      sqlite3OomFault(db);
      return;
    }
    pParse->pNewTable = 0;
    db->mDbFlags |= DBFLAG_SchemaChange;

#ifndef SQLITE_OMIT_ALTERTABLE
    if( !p->pSelect ){
      const char *zName = (const char *)pParse->sNameToken.z;
      int nName;
      assert( !pSelect && pCons && pEnd );
      if( pCons->z==0 ){
        pCons = pEnd;
      }
      nName = (int)((const char *)pCons->z - zName);
      p->addColOffset = 13 + sqlite3Utf8CharLen(zName, nName);
    }
#endif
  }
}