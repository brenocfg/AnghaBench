#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  aSzDel ;
struct TYPE_11__ {int bHasStat; scalar_t__ pSegments; int nColumn; scalar_t__ zContentTbl; scalar_t__ bFts4; scalar_t__ bHasDocsize; int /*<<< orphan*/  iPrevDocid; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int FTS_CORRUPT_VTAB ; 
 int SQLITE_CONSTRAINT ; 
 scalar_t__ SQLITE_INTEGER ; 
 int SQLITE_NOMEM ; 
 scalar_t__ SQLITE_NULL ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_REPLACE ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3DeleteByRowid (TYPE_1__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int fts3InsertData (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts3InsertDocsize (int*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int fts3InsertTerms (TYPE_1__*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int fts3PendingTermsDocid (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int fts3SpecialInsert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts3UpdateDocTotals (int*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int fts3Writelock (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts3SegmentsClose (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_malloc64 (int) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_vtab_on_conflict (int /*<<< orphan*/ ) ; 

int sqlite3Fts3UpdateMethod(
  sqlite3_vtab *pVtab,            /* FTS3 vtab object */
  int nArg,                       /* Size of argument array */
  sqlite3_value **apVal,          /* Array of arguments */
  sqlite_int64 *pRowid            /* OUT: The affected (or effected) rowid */
){
  Fts3Table *p = (Fts3Table *)pVtab;
  int rc = SQLITE_OK;             /* Return Code */
  u32 *aSzIns = 0;                /* Sizes of inserted documents */
  u32 *aSzDel = 0;                /* Sizes of deleted documents */
  int nChng = 0;                  /* Net change in number of documents */
  int bInsertDone = 0;

  /* At this point it must be known if the %_stat table exists or not.
  ** So bHasStat may not be 2.  */
  assert( p->bHasStat==0 || p->bHasStat==1 );

  assert( p->pSegments==0 );
  assert( 
      nArg==1                     /* DELETE operations */
   || nArg==(2 + p->nColumn + 3)  /* INSERT or UPDATE operations */
  );

  /* Check for a "special" INSERT operation. One of the form:
  **
  **   INSERT INTO xyz(xyz) VALUES('command');
  */
  if( nArg>1 
   && sqlite3_value_type(apVal[0])==SQLITE_NULL 
   && sqlite3_value_type(apVal[p->nColumn+2])!=SQLITE_NULL 
  ){
    rc = fts3SpecialInsert(p, apVal[p->nColumn+2]);
    goto update_out;
  }

  if( nArg>1 && sqlite3_value_int(apVal[2 + p->nColumn + 2])<0 ){
    rc = SQLITE_CONSTRAINT;
    goto update_out;
  }

  /* Allocate space to hold the change in document sizes */
  aSzDel = sqlite3_malloc64(sizeof(aSzDel[0])*((sqlite3_int64)p->nColumn+1)*2);
  if( aSzDel==0 ){
    rc = SQLITE_NOMEM;
    goto update_out;
  }
  aSzIns = &aSzDel[p->nColumn+1];
  memset(aSzDel, 0, sizeof(aSzDel[0])*(p->nColumn+1)*2);

  rc = fts3Writelock(p);
  if( rc!=SQLITE_OK ) goto update_out;

  /* If this is an INSERT operation, or an UPDATE that modifies the rowid
  ** value, then this operation requires constraint handling.
  **
  ** If the on-conflict mode is REPLACE, this means that the existing row
  ** should be deleted from the database before inserting the new row. Or,
  ** if the on-conflict mode is other than REPLACE, then this method must
  ** detect the conflict and return SQLITE_CONSTRAINT before beginning to
  ** modify the database file.
  */
  if( nArg>1 && p->zContentTbl==0 ){
    /* Find the value object that holds the new rowid value. */
    sqlite3_value *pNewRowid = apVal[3+p->nColumn];
    if( sqlite3_value_type(pNewRowid)==SQLITE_NULL ){
      pNewRowid = apVal[1];
    }

    if( sqlite3_value_type(pNewRowid)!=SQLITE_NULL && ( 
        sqlite3_value_type(apVal[0])==SQLITE_NULL
     || sqlite3_value_int64(apVal[0])!=sqlite3_value_int64(pNewRowid)
    )){
      /* The new rowid is not NULL (in this case the rowid will be
      ** automatically assigned and there is no chance of a conflict), and 
      ** the statement is either an INSERT or an UPDATE that modifies the
      ** rowid column. So if the conflict mode is REPLACE, then delete any
      ** existing row with rowid=pNewRowid. 
      **
      ** Or, if the conflict mode is not REPLACE, insert the new record into 
      ** the %_content table. If we hit the duplicate rowid constraint (or any
      ** other error) while doing so, return immediately.
      **
      ** This branch may also run if pNewRowid contains a value that cannot
      ** be losslessly converted to an integer. In this case, the eventual 
      ** call to fts3InsertData() (either just below or further on in this
      ** function) will return SQLITE_MISMATCH. If fts3DeleteByRowid is 
      ** invoked, it will delete zero rows (since no row will have
      ** docid=$pNewRowid if $pNewRowid is not an integer value).
      */
      if( sqlite3_vtab_on_conflict(p->db)==SQLITE_REPLACE ){
        rc = fts3DeleteByRowid(p, pNewRowid, &nChng, aSzDel);
      }else{
        rc = fts3InsertData(p, apVal, pRowid);
        bInsertDone = 1;
      }
    }
  }
  if( rc!=SQLITE_OK ){
    goto update_out;
  }

  /* If this is a DELETE or UPDATE operation, remove the old record. */
  if( sqlite3_value_type(apVal[0])!=SQLITE_NULL ){
    assert( sqlite3_value_type(apVal[0])==SQLITE_INTEGER );
    rc = fts3DeleteByRowid(p, apVal[0], &nChng, aSzDel);
  }
  
  /* If this is an INSERT or UPDATE operation, insert the new record. */
  if( nArg>1 && rc==SQLITE_OK ){
    int iLangid = sqlite3_value_int(apVal[2 + p->nColumn + 2]);
    if( bInsertDone==0 ){
      rc = fts3InsertData(p, apVal, pRowid);
      if( rc==SQLITE_CONSTRAINT && p->zContentTbl==0 ){
        rc = FTS_CORRUPT_VTAB;
      }
    }
    if( rc==SQLITE_OK ){
      rc = fts3PendingTermsDocid(p, 0, iLangid, *pRowid);
    }
    if( rc==SQLITE_OK ){
      assert( p->iPrevDocid==*pRowid );
      rc = fts3InsertTerms(p, iLangid, apVal, aSzIns);
    }
    if( p->bHasDocsize ){
      fts3InsertDocsize(&rc, p, aSzIns);
    }
    nChng++;
  }

  if( p->bFts4 ){
    fts3UpdateDocTotals(&rc, p, aSzIns, aSzDel, nChng);
  }

 update_out:
  sqlite3_free(aSzDel);
  sqlite3Fts3SegmentsClose(p);
  return rc;
}