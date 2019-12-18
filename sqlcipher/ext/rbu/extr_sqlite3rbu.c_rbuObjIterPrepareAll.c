#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {char* zErrmsg; scalar_t__ rc; int /*<<< orphan*/  dbRbu; int /*<<< orphan*/  dbMain; int /*<<< orphan*/  zStateDb; } ;
typedef  TYPE_1__ sqlite3rbu ;
struct TYPE_27__ {scalar_t__ bCleanup; scalar_t__ pSelect; int iTnum; char* zIdx; char* zTbl; scalar_t__ eType; int nCol; scalar_t__ pInsert; scalar_t__ pDelete; char* zDataTbl; int nTblCol; scalar_t__ abIndexed; } ;
typedef  TYPE_2__ RbuObjIter ;

/* Variables and functions */
 scalar_t__ RBU_PK_EXTERNAL ; 
 scalar_t__ RBU_PK_NONE ; 
 scalar_t__ RBU_PK_VTAB ; 
 scalar_t__ SQLITE_NOMEM ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TESTCTRL_IMPOSTER ; 
 int /*<<< orphan*/  assert (int) ; 
 void* prepareFreeAndCollectError (int /*<<< orphan*/ ,scalar_t__*,char**,char*) ; 
 int /*<<< orphan*/  rbuCreateImposterTable (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  rbuCreateImposterTable2 (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ rbuIsVacuum (TYPE_1__*) ; 
 int /*<<< orphan*/  rbuMPrintfExec (TYPE_1__*,int /*<<< orphan*/ ,char*,char const*,char const*,char*,...) ; 
 scalar_t__ rbuObjIterCacheTableInfo (TYPE_1__*,TYPE_2__*) ; 
 char* rbuObjIterGetBindlist (TYPE_1__*,int) ; 
 char* rbuObjIterGetCollist (TYPE_1__*,TYPE_2__*) ; 
 char* rbuObjIterGetIndexCols (TYPE_1__*,TYPE_2__*,char**,char**,char**,int*) ; 
 char* rbuObjIterGetIndexWhere (TYPE_1__*,TYPE_2__*) ; 
 char* rbuObjIterGetOldlist (TYPE_1__*,TYPE_2__*,char*) ; 
 char* rbuObjIterGetWhere (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  rbuObjIterPrepareTmpInsert (TYPE_1__*,TYPE_2__*,char*,char const*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_test_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int const) ; 

__attribute__((used)) static int rbuObjIterPrepareAll(
  sqlite3rbu *p, 
  RbuObjIter *pIter,
  int nOffset                     /* Add "LIMIT -1 OFFSET $nOffset" to SELECT */
){
  assert( pIter->bCleanup==0 );
  if( pIter->pSelect==0 && rbuObjIterCacheTableInfo(p, pIter)==SQLITE_OK ){
    const int tnum = pIter->iTnum;
    char *zCollist = 0;           /* List of indexed columns */
    char **pz = &p->zErrmsg;
    const char *zIdx = pIter->zIdx;
    char *zLimit = 0;

    if( nOffset ){
      zLimit = sqlite3_mprintf(" LIMIT -1 OFFSET %d", nOffset);
      if( !zLimit ) p->rc = SQLITE_NOMEM;
    }

    if( zIdx ){
      const char *zTbl = pIter->zTbl;
      char *zImposterCols = 0;    /* Columns for imposter table */
      char *zImposterPK = 0;      /* Primary key declaration for imposter */
      char *zWhere = 0;           /* WHERE clause on PK columns */
      char *zBind = 0;
      char *zPart = 0;
      int nBind = 0;

      assert( pIter->eType!=RBU_PK_VTAB );
      zCollist = rbuObjIterGetIndexCols(
          p, pIter, &zImposterCols, &zImposterPK, &zWhere, &nBind
      );
      zBind = rbuObjIterGetBindlist(p, nBind);
      zPart = rbuObjIterGetIndexWhere(p, pIter);

      /* Create the imposter table used to write to this index. */
      sqlite3_test_control(SQLITE_TESTCTRL_IMPOSTER, p->dbMain, "main", 0, 1);
      sqlite3_test_control(SQLITE_TESTCTRL_IMPOSTER, p->dbMain, "main", 1,tnum);
      rbuMPrintfExec(p, p->dbMain,
          "CREATE TABLE \"rbu_imp_%w\"( %s, PRIMARY KEY( %s ) ) WITHOUT ROWID",
          zTbl, zImposterCols, zImposterPK
      );
      sqlite3_test_control(SQLITE_TESTCTRL_IMPOSTER, p->dbMain, "main", 0, 0);

      /* Create the statement to insert index entries */
      pIter->nCol = nBind;
      if( p->rc==SQLITE_OK ){
        p->rc = prepareFreeAndCollectError(
            p->dbMain, &pIter->pInsert, &p->zErrmsg,
          sqlite3_mprintf("INSERT INTO \"rbu_imp_%w\" VALUES(%s)", zTbl, zBind)
        );
      }

      /* And to delete index entries */
      if( rbuIsVacuum(p)==0 && p->rc==SQLITE_OK ){
        p->rc = prepareFreeAndCollectError(
            p->dbMain, &pIter->pDelete, &p->zErrmsg,
          sqlite3_mprintf("DELETE FROM \"rbu_imp_%w\" WHERE %s", zTbl, zWhere)
        );
      }

      /* Create the SELECT statement to read keys in sorted order */
      if( p->rc==SQLITE_OK ){
        char *zSql;
        if( rbuIsVacuum(p) ){
          zSql = sqlite3_mprintf(
              "SELECT %s, 0 AS rbu_control FROM '%q' %s ORDER BY %s%s",
              zCollist, 
              pIter->zDataTbl,
              zPart, zCollist, zLimit
          );
        }else

        if( pIter->eType==RBU_PK_EXTERNAL || pIter->eType==RBU_PK_NONE ){
          zSql = sqlite3_mprintf(
              "SELECT %s, rbu_control FROM %s.'rbu_tmp_%q' %s ORDER BY %s%s",
              zCollist, p->zStateDb, pIter->zDataTbl,
              zPart, zCollist, zLimit
          );
        }else{
          zSql = sqlite3_mprintf(
              "SELECT %s, rbu_control FROM %s.'rbu_tmp_%q' %s "
              "UNION ALL "
              "SELECT %s, rbu_control FROM '%q' "
              "%s %s typeof(rbu_control)='integer' AND rbu_control!=1 "
              "ORDER BY %s%s",
              zCollist, p->zStateDb, pIter->zDataTbl, zPart,
              zCollist, pIter->zDataTbl, 
              zPart,
              (zPart ? "AND" : "WHERE"),
              zCollist, zLimit
          );
        }
        p->rc = prepareFreeAndCollectError(p->dbRbu, &pIter->pSelect, pz, zSql);
      }

      sqlite3_free(zImposterCols);
      sqlite3_free(zImposterPK);
      sqlite3_free(zWhere);
      sqlite3_free(zBind);
      sqlite3_free(zPart);
    }else{
      int bRbuRowid = (pIter->eType==RBU_PK_VTAB)
                    ||(pIter->eType==RBU_PK_NONE)
                    ||(pIter->eType==RBU_PK_EXTERNAL && rbuIsVacuum(p));
      const char *zTbl = pIter->zTbl;       /* Table this step applies to */
      const char *zWrite;                   /* Imposter table name */

      char *zBindings = rbuObjIterGetBindlist(p, pIter->nTblCol + bRbuRowid);
      char *zWhere = rbuObjIterGetWhere(p, pIter);
      char *zOldlist = rbuObjIterGetOldlist(p, pIter, "old");
      char *zNewlist = rbuObjIterGetOldlist(p, pIter, "new");

      zCollist = rbuObjIterGetCollist(p, pIter);
      pIter->nCol = pIter->nTblCol;

      /* Create the imposter table or tables (if required). */
      rbuCreateImposterTable(p, pIter);
      rbuCreateImposterTable2(p, pIter);
      zWrite = (pIter->eType==RBU_PK_VTAB ? "" : "rbu_imp_");

      /* Create the INSERT statement to write to the target PK b-tree */
      if( p->rc==SQLITE_OK ){
        p->rc = prepareFreeAndCollectError(p->dbMain, &pIter->pInsert, pz,
            sqlite3_mprintf(
              "INSERT INTO \"%s%w\"(%s%s) VALUES(%s)", 
              zWrite, zTbl, zCollist, (bRbuRowid ? ", _rowid_" : ""), zBindings
            )
        );
      }

      /* Create the DELETE statement to write to the target PK b-tree.
      ** Because it only performs INSERT operations, this is not required for
      ** an rbu vacuum handle.  */
      if( rbuIsVacuum(p)==0 && p->rc==SQLITE_OK ){
        p->rc = prepareFreeAndCollectError(p->dbMain, &pIter->pDelete, pz,
            sqlite3_mprintf(
              "DELETE FROM \"%s%w\" WHERE %s", zWrite, zTbl, zWhere
            )
        );
      }

      if( rbuIsVacuum(p)==0 && pIter->abIndexed ){
        const char *zRbuRowid = "";
        if( pIter->eType==RBU_PK_EXTERNAL || pIter->eType==RBU_PK_NONE ){
          zRbuRowid = ", rbu_rowid";
        }

        /* Create the rbu_tmp_xxx table and the triggers to populate it. */
        rbuMPrintfExec(p, p->dbRbu,
            "CREATE TABLE IF NOT EXISTS %s.'rbu_tmp_%q' AS "
            "SELECT *%s FROM '%q' WHERE 0;"
            , p->zStateDb, pIter->zDataTbl
            , (pIter->eType==RBU_PK_EXTERNAL ? ", 0 AS rbu_rowid" : "")
            , pIter->zDataTbl
        );

        rbuMPrintfExec(p, p->dbMain,
            "CREATE TEMP TRIGGER rbu_delete_tr BEFORE DELETE ON \"%s%w\" "
            "BEGIN "
            "  SELECT rbu_tmp_insert(3, %s);"
            "END;"

            "CREATE TEMP TRIGGER rbu_update1_tr BEFORE UPDATE ON \"%s%w\" "
            "BEGIN "
            "  SELECT rbu_tmp_insert(3, %s);"
            "END;"

            "CREATE TEMP TRIGGER rbu_update2_tr AFTER UPDATE ON \"%s%w\" "
            "BEGIN "
            "  SELECT rbu_tmp_insert(4, %s);"
            "END;",
            zWrite, zTbl, zOldlist,
            zWrite, zTbl, zOldlist,
            zWrite, zTbl, zNewlist
        );

        if( pIter->eType==RBU_PK_EXTERNAL || pIter->eType==RBU_PK_NONE ){
          rbuMPrintfExec(p, p->dbMain,
              "CREATE TEMP TRIGGER rbu_insert_tr AFTER INSERT ON \"%s%w\" "
              "BEGIN "
              "  SELECT rbu_tmp_insert(0, %s);"
              "END;",
              zWrite, zTbl, zNewlist
          );
        }

        rbuObjIterPrepareTmpInsert(p, pIter, zCollist, zRbuRowid);
      }

      /* Create the SELECT statement to read keys from data_xxx */
      if( p->rc==SQLITE_OK ){
        const char *zRbuRowid = "";
        if( bRbuRowid ){
          zRbuRowid = rbuIsVacuum(p) ? ",_rowid_ " : ",rbu_rowid";
        }
        p->rc = prepareFreeAndCollectError(p->dbRbu, &pIter->pSelect, pz,
            sqlite3_mprintf(
              "SELECT %s,%s rbu_control%s FROM '%q'%s", 
              zCollist, 
              (rbuIsVacuum(p) ? "0 AS " : ""),
              zRbuRowid,
              pIter->zDataTbl, zLimit
            )
        );
      }

      sqlite3_free(zWhere);
      sqlite3_free(zOldlist);
      sqlite3_free(zNewlist);
      sqlite3_free(zBindings);
    }
    sqlite3_free(zCollist);
    sqlite3_free(zLimit);
  }
  
  return p->rc;
}