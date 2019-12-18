#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_40__ {int /*<<< orphan*/  mDbFlags; TYPE_1__* aDb; int /*<<< orphan*/  mallocFailed; } ;
typedef  TYPE_4__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_41__ {TYPE_3__* pVtab; } ;
typedef  TYPE_5__ VTable ;
typedef  int /*<<< orphan*/  Token ;
struct TYPE_42__ {char* zName; scalar_t__ pSelect; int /*<<< orphan*/  pSchema; } ;
typedef  TYPE_6__ Table ;
struct TYPE_44__ {int nMem; TYPE_4__* db; } ;
struct TYPE_43__ {int nSrc; int /*<<< orphan*/ * a; } ;
struct TYPE_39__ {TYPE_2__* pModule; } ;
struct TYPE_38__ {scalar_t__ xRename; } ;
struct TYPE_37__ {char* zDbSName; } ;
typedef  TYPE_7__ SrcList ;
typedef  TYPE_8__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  DBFLAG_PreferBuiltin ; 
 scalar_t__ IsVirtual (TYPE_6__*) ; 
 int /*<<< orphan*/  MASTER_NAME ; 
 scalar_t__ NEVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_VRename ; 
 int /*<<< orphan*/  P4_VTAB ; 
 int /*<<< orphan*/  SQLITE_ALTER_TABLE ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isAlterableTable (TYPE_8__*,TYPE_6__*) ; 
 int /*<<< orphan*/  renameReloadSchema (TYPE_8__*,int) ; 
 int /*<<< orphan*/  renameTestSchema (TYPE_8__*,char*,int) ; 
 scalar_t__ sqlite3AuthCheck (TYPE_8__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int sqlite3BtreeHoldsAllMutexes (TYPE_4__*) ; 
 scalar_t__ sqlite3CheckObjectName (TYPE_8__*,char*) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_8__*,char*,char*) ; 
 scalar_t__ sqlite3FindIndex (TYPE_4__*,char*,char*) ; 
 scalar_t__ sqlite3FindTable (TYPE_4__*,char*,char*) ; 
 TYPE_5__* sqlite3GetVTable (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_8__*) ; 
 TYPE_6__* sqlite3LocateTableItem (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3MayAbort (TYPE_8__*) ; 
 char* sqlite3NameFromToken (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3NestedParse (TYPE_8__*,char*,char*,char const*,char*,...) ; 
 int sqlite3SchemaToIndex (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListDelete (TYPE_4__*,TYPE_7__*) ; 
 int sqlite3Utf8CharLen (char const*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeLoadString (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ sqlite3ViewGetColumnNames (TYPE_8__*,TYPE_6__*) ; 

void sqlite3AlterRenameTable(
  Parse *pParse,            /* Parser context. */
  SrcList *pSrc,            /* The table to rename. */
  Token *pName              /* The new table name. */
){
  int iDb;                  /* Database that contains the table */
  char *zDb;                /* Name of database iDb */
  Table *pTab;              /* Table being renamed */
  char *zName = 0;          /* NULL-terminated version of pName */ 
  sqlite3 *db = pParse->db; /* Database connection */
  int nTabName;             /* Number of UTF-8 characters in zTabName */
  const char *zTabName;     /* Original name of the table */
  Vdbe *v;
  VTable *pVTab = 0;        /* Non-zero if this is a v-tab with an xRename() */
  u32 savedDbFlags;         /* Saved value of db->mDbFlags */

  savedDbFlags = db->mDbFlags;  
  if( NEVER(db->mallocFailed) ) goto exit_rename_table;
  assert( pSrc->nSrc==1 );
  assert( sqlite3BtreeHoldsAllMutexes(pParse->db) );

  pTab = sqlite3LocateTableItem(pParse, 0, &pSrc->a[0]);
  if( !pTab ) goto exit_rename_table;
  iDb = sqlite3SchemaToIndex(pParse->db, pTab->pSchema);
  zDb = db->aDb[iDb].zDbSName;
  db->mDbFlags |= DBFLAG_PreferBuiltin;

  /* Get a NULL terminated version of the new table name. */
  zName = sqlite3NameFromToken(db, pName);
  if( !zName ) goto exit_rename_table;

  /* Check that a table or index named 'zName' does not already exist
  ** in database iDb. If so, this is an error.
  */
  if( sqlite3FindTable(db, zName, zDb) || sqlite3FindIndex(db, zName, zDb) ){
    sqlite3ErrorMsg(pParse, 
        "there is already another table or index with this name: %s", zName);
    goto exit_rename_table;
  }

  /* Make sure it is not a system table being altered, or a reserved name
  ** that the table is being renamed to.
  */
  if( SQLITE_OK!=isAlterableTable(pParse, pTab) ){
    goto exit_rename_table;
  }
  if( SQLITE_OK!=sqlite3CheckObjectName(pParse, zName) ){ goto
    exit_rename_table;
  }

#ifndef SQLITE_OMIT_VIEW
  if( pTab->pSelect ){
    sqlite3ErrorMsg(pParse, "view %s may not be altered", pTab->zName);
    goto exit_rename_table;
  }
#endif

#ifndef SQLITE_OMIT_AUTHORIZATION
  /* Invoke the authorization callback. */
  if( sqlite3AuthCheck(pParse, SQLITE_ALTER_TABLE, zDb, pTab->zName, 0) ){
    goto exit_rename_table;
  }
#endif

#ifndef SQLITE_OMIT_VIRTUALTABLE
  if( sqlite3ViewGetColumnNames(pParse, pTab) ){
    goto exit_rename_table;
  }
  if( IsVirtual(pTab) ){
    pVTab = sqlite3GetVTable(db, pTab);
    if( pVTab->pVtab->pModule->xRename==0 ){
      pVTab = 0;
    }
  }
#endif

  /* Begin a transaction for database iDb. Then modify the schema cookie
  ** (since the ALTER TABLE modifies the schema). Call sqlite3MayAbort(),
  ** as the scalar functions (e.g. sqlite_rename_table()) invoked by the 
  ** nested SQL may raise an exception.  */
  v = sqlite3GetVdbe(pParse);
  if( v==0 ){
    goto exit_rename_table;
  }
  sqlite3MayAbort(pParse);

  /* figure out how many UTF-8 characters are in zName */
  zTabName = pTab->zName;
  nTabName = sqlite3Utf8CharLen(zTabName, -1);

  /* Rewrite all CREATE TABLE, INDEX, TRIGGER or VIEW statements in
  ** the schema to use the new table name.  */
  sqlite3NestedParse(pParse, 
      "UPDATE \"%w\".%s SET "
      "sql = sqlite_rename_table(%Q, type, name, sql, %Q, %Q, %d) "
      "WHERE (type!='index' OR tbl_name=%Q COLLATE nocase)"
      "AND   name NOT LIKE 'sqlite_%%'"
      , zDb, MASTER_NAME, zDb, zTabName, zName, (iDb==1), zTabName
  );

  /* Update the tbl_name and name columns of the sqlite_master table
  ** as required.  */
  sqlite3NestedParse(pParse,
      "UPDATE %Q.%s SET "
          "tbl_name = %Q, "
          "name = CASE "
            "WHEN type='table' THEN %Q "
            "WHEN name LIKE 'sqlite_autoindex%%' AND type='index' THEN "
             "'sqlite_autoindex_' || %Q || substr(name,%d+18) "
            "ELSE name END "
      "WHERE tbl_name=%Q COLLATE nocase AND "
          "(type='table' OR type='index' OR type='trigger');", 
      zDb, MASTER_NAME, 
      zName, zName, zName, 
      nTabName, zTabName
  );

#ifndef SQLITE_OMIT_AUTOINCREMENT
  /* If the sqlite_sequence table exists in this database, then update 
  ** it with the new table name.
  */
  if( sqlite3FindTable(db, "sqlite_sequence", zDb) ){
    sqlite3NestedParse(pParse,
        "UPDATE \"%w\".sqlite_sequence set name = %Q WHERE name = %Q",
        zDb, zName, pTab->zName);
  }
#endif

  /* If the table being renamed is not itself part of the temp database,
  ** edit view and trigger definitions within the temp database 
  ** as required.  */
  if( iDb!=1 ){
    sqlite3NestedParse(pParse, 
        "UPDATE sqlite_temp_master SET "
            "sql = sqlite_rename_table(%Q, type, name, sql, %Q, %Q, 1), "
            "tbl_name = "
              "CASE WHEN tbl_name=%Q COLLATE nocase AND "
              "          sqlite_rename_test(%Q, sql, type, name, 1) "
              "THEN %Q ELSE tbl_name END "
            "WHERE type IN ('view', 'trigger')"
        , zDb, zTabName, zName, zTabName, zDb, zName);
  }

  /* If this is a virtual table, invoke the xRename() function if
  ** one is defined. The xRename() callback will modify the names
  ** of any resources used by the v-table implementation (including other
  ** SQLite tables) that are identified by the name of the virtual table.
  */
#ifndef SQLITE_OMIT_VIRTUALTABLE
  if( pVTab ){
    int i = ++pParse->nMem;
    sqlite3VdbeLoadString(v, i, zName);
    sqlite3VdbeAddOp4(v, OP_VRename, i, 0, 0,(const char*)pVTab, P4_VTAB);
  }
#endif

  renameReloadSchema(pParse, iDb);
  renameTestSchema(pParse, zDb, iDb==1);

exit_rename_table:
  sqlite3SrcListDelete(db, pSrc);
  sqlite3DbFree(db, zName);
  db->mDbFlags = savedDbFlags;
}