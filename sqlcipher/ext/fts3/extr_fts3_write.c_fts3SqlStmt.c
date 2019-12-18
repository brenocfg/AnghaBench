#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  char const sqlite3_stmt ;
struct TYPE_3__ {char const** aStmt; int /*<<< orphan*/  db; int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; int /*<<< orphan*/  zReadExprlist; int /*<<< orphan*/  zWriteExprlist; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_PREPARE_NO_VTAB ; 
 int SQLITE_PREPARE_PERSISTENT ; 
 int SQL_CONTENT_INSERT ; 
 int SQL_SELECT_CONTENT_BY_ROWID ; 
 int SizeofArray (char const**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3_bind_parameter_count (char const*) ; 
 int sqlite3_bind_value (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char const*,int /*<<< orphan*/ ,...) ; 
 int sqlite3_prepare_v3 (int /*<<< orphan*/ ,char*,int,int,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3SqlStmt(
  Fts3Table *p,                   /* Virtual table handle */
  int eStmt,                      /* One of the SQL_XXX constants above */
  sqlite3_stmt **pp,              /* OUT: Statement handle */
  sqlite3_value **apVal           /* Values to bind to statement */
){
  const char *azSql[] = {
/* 0  */  "DELETE FROM %Q.'%q_content' WHERE rowid = ?",
/* 1  */  "SELECT NOT EXISTS(SELECT docid FROM %Q.'%q_content' WHERE rowid!=?)",
/* 2  */  "DELETE FROM %Q.'%q_content'",
/* 3  */  "DELETE FROM %Q.'%q_segments'",
/* 4  */  "DELETE FROM %Q.'%q_segdir'",
/* 5  */  "DELETE FROM %Q.'%q_docsize'",
/* 6  */  "DELETE FROM %Q.'%q_stat'",
/* 7  */  "SELECT %s WHERE rowid=?",
/* 8  */  "SELECT (SELECT max(idx) FROM %Q.'%q_segdir' WHERE level = ?) + 1",
/* 9  */  "REPLACE INTO %Q.'%q_segments'(blockid, block) VALUES(?, ?)",
/* 10 */  "SELECT coalesce((SELECT max(blockid) FROM %Q.'%q_segments') + 1, 1)",
/* 11 */  "REPLACE INTO %Q.'%q_segdir' VALUES(?,?,?,?,?,?)",

          /* Return segments in order from oldest to newest.*/ 
/* 12 */  "SELECT idx, start_block, leaves_end_block, end_block, root "
            "FROM %Q.'%q_segdir' WHERE level = ? ORDER BY idx ASC",
/* 13 */  "SELECT idx, start_block, leaves_end_block, end_block, root "
            "FROM %Q.'%q_segdir' WHERE level BETWEEN ? AND ?"
            "ORDER BY level DESC, idx ASC",

/* 14 */  "SELECT count(*) FROM %Q.'%q_segdir' WHERE level = ?",
/* 15 */  "SELECT max(level) FROM %Q.'%q_segdir' WHERE level BETWEEN ? AND ?",

/* 16 */  "DELETE FROM %Q.'%q_segdir' WHERE level = ?",
/* 17 */  "DELETE FROM %Q.'%q_segments' WHERE blockid BETWEEN ? AND ?",
/* 18 */  "INSERT INTO %Q.'%q_content' VALUES(%s)",
/* 19 */  "DELETE FROM %Q.'%q_docsize' WHERE docid = ?",
/* 20 */  "REPLACE INTO %Q.'%q_docsize' VALUES(?,?)",
/* 21 */  "SELECT size FROM %Q.'%q_docsize' WHERE docid=?",
/* 22 */  "SELECT value FROM %Q.'%q_stat' WHERE id=?",
/* 23 */  "REPLACE INTO %Q.'%q_stat' VALUES(?,?)",
/* 24 */  "",
/* 25 */  "",

/* 26 */ "DELETE FROM %Q.'%q_segdir' WHERE level BETWEEN ? AND ?",
/* 27 */ "SELECT ? UNION SELECT level / (1024 * ?) FROM %Q.'%q_segdir'",

/* This statement is used to determine which level to read the input from
** when performing an incremental merge. It returns the absolute level number
** of the oldest level in the db that contains at least ? segments. Or,
** if no level in the FTS index contains more than ? segments, the statement
** returns zero rows.  */
/* 28 */ "SELECT level, count(*) AS cnt FROM %Q.'%q_segdir' "
         "  GROUP BY level HAVING cnt>=?"
         "  ORDER BY (level %% 1024) ASC LIMIT 1",

/* Estimate the upper limit on the number of leaf nodes in a new segment
** created by merging the oldest :2 segments from absolute level :1. See 
** function sqlite3Fts3Incrmerge() for details.  */
/* 29 */ "SELECT 2 * total(1 + leaves_end_block - start_block) "
         "  FROM %Q.'%q_segdir' WHERE level = ? AND idx < ?",

/* SQL_DELETE_SEGDIR_ENTRY
**   Delete the %_segdir entry on absolute level :1 with index :2.  */
/* 30 */ "DELETE FROM %Q.'%q_segdir' WHERE level = ? AND idx = ?",

/* SQL_SHIFT_SEGDIR_ENTRY
**   Modify the idx value for the segment with idx=:3 on absolute level :2
**   to :1.  */
/* 31 */ "UPDATE %Q.'%q_segdir' SET idx = ? WHERE level=? AND idx=?",

/* SQL_SELECT_SEGDIR
**   Read a single entry from the %_segdir table. The entry from absolute 
**   level :1 with index value :2.  */
/* 32 */  "SELECT idx, start_block, leaves_end_block, end_block, root "
            "FROM %Q.'%q_segdir' WHERE level = ? AND idx = ?",

/* SQL_CHOMP_SEGDIR
**   Update the start_block (:1) and root (:2) fields of the %_segdir
**   entry located on absolute level :3 with index :4.  */
/* 33 */  "UPDATE %Q.'%q_segdir' SET start_block = ?, root = ?"
            "WHERE level = ? AND idx = ?",

/* SQL_SEGMENT_IS_APPENDABLE
**   Return a single row if the segment with end_block=? is appendable. Or
**   no rows otherwise.  */
/* 34 */  "SELECT 1 FROM %Q.'%q_segments' WHERE blockid=? AND block IS NULL",

/* SQL_SELECT_INDEXES
**   Return the list of valid segment indexes for absolute level ?  */
/* 35 */  "SELECT idx FROM %Q.'%q_segdir' WHERE level=? ORDER BY 1 ASC",

/* SQL_SELECT_MXLEVEL
**   Return the largest relative level in the FTS index or indexes.  */
/* 36 */  "SELECT max( level %% 1024 ) FROM %Q.'%q_segdir'",

          /* Return segments in order from oldest to newest.*/ 
/* 37 */  "SELECT level, idx, end_block "
            "FROM %Q.'%q_segdir' WHERE level BETWEEN ? AND ? "
            "ORDER BY level DESC, idx ASC",

          /* Update statements used while promoting segments */
/* 38 */  "UPDATE OR FAIL %Q.'%q_segdir' SET level=-1,idx=? "
            "WHERE level=? AND idx=?",
/* 39 */  "UPDATE OR FAIL %Q.'%q_segdir' SET level=? WHERE level=-1"

  };
  int rc = SQLITE_OK;
  sqlite3_stmt *pStmt;

  assert( SizeofArray(azSql)==SizeofArray(p->aStmt) );
  assert( eStmt<SizeofArray(azSql) && eStmt>=0 );
  
  pStmt = p->aStmt[eStmt];
  if( !pStmt ){
    int f = SQLITE_PREPARE_PERSISTENT|SQLITE_PREPARE_NO_VTAB;
    char *zSql;
    if( eStmt==SQL_CONTENT_INSERT ){
      zSql = sqlite3_mprintf(azSql[eStmt], p->zDb, p->zName, p->zWriteExprlist);
    }else if( eStmt==SQL_SELECT_CONTENT_BY_ROWID ){
      f &= ~SQLITE_PREPARE_NO_VTAB;
      zSql = sqlite3_mprintf(azSql[eStmt], p->zReadExprlist);
    }else{
      zSql = sqlite3_mprintf(azSql[eStmt], p->zDb, p->zName);
    }
    if( !zSql ){
      rc = SQLITE_NOMEM;
    }else{
      rc = sqlite3_prepare_v3(p->db, zSql, -1, f, &pStmt, NULL);
      sqlite3_free(zSql);
      assert( rc==SQLITE_OK || pStmt==0 );
      p->aStmt[eStmt] = pStmt;
    }
  }
  if( apVal ){
    int i;
    int nParam = sqlite3_bind_parameter_count(pStmt);
    for(i=0; rc==SQLITE_OK && i<nParam; i++){
      rc = sqlite3_bind_value(pStmt, i+1, apVal[i]);
    }
  }
  *pp = pStmt;
  return rc;
}