#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_7__ {int nRow; int idxNum; int nAlloc; TYPE_1__* a; int /*<<< orphan*/  nSearch; } ;
typedef  TYPE_2__ spellfix1_cursor ;
struct TYPE_8__ {int iScope; int rc; int nRun; char** azPrior; int iMaxDist; int /*<<< orphan*/  zPattern; int /*<<< orphan*/  pLang; scalar_t__ pMatchStr3; int /*<<< orphan*/ * pStmt; TYPE_2__* pCur; } ;
struct TYPE_6__ {int iScore; char* zWord; int iRank; int iDistance; int iMatchlen; char* zHash; int /*<<< orphan*/  iRowid; } ;
typedef  TYPE_3__ MatchQuery ;

/* Variables and functions */
 int SPELLFIX_IDXNUM_DIST ; 
 int SPELLFIX_IDXNUM_TOP ; 
 int SPELLFIX_MX_HASH ; 
 int SPELLFIX_MX_RUN ; 
 scalar_t__ SQLITE_NOMEM ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int editDist3Core (scalar_t__,char const*,int,int /*<<< orphan*/ ,int*) ; 
 int editdist1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ phoneticHash (unsigned char*,int) ; 
 int /*<<< orphan*/  spellfix1ResizeCursor (TYPE_2__*,int) ; 
 int spellfix1Score (int,int) ; 
 scalar_t__ sqlite3_bind_text (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,scalar_t__) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void spellfix1RunQuery(MatchQuery *p, const char *zQuery, int nQuery){
  const char *zK1;
  const char *zWord;
  int iDist;
  int iRank;
  int iScore;
  int iWorst = 0;
  int idx;
  int idxWorst = -1;
  int i;
  int iScope = p->iScope;
  spellfix1_cursor *pCur = p->pCur;
  sqlite3_stmt *pStmt = p->pStmt;
  char zHash1[SPELLFIX_MX_HASH];
  char zHash2[SPELLFIX_MX_HASH];
  char *zClass;
  int nClass;
  int rc;

  if( pCur->a==0 || p->rc ) return;   /* Prior memory allocation failure */
  zClass = (char*)phoneticHash((unsigned char*)zQuery, nQuery);
  if( zClass==0 ){
    p->rc = SQLITE_NOMEM;
    return;
  }
  nClass = (int)strlen(zClass);
  if( nClass>SPELLFIX_MX_HASH-2 ){
    nClass = SPELLFIX_MX_HASH-2;
    zClass[nClass] = 0;
  }
  if( nClass<=iScope ){
    if( nClass>2 ){
      iScope = nClass-1;
    }else{
      iScope = nClass;
    }
  }
  memcpy(zHash1, zClass, iScope);
  sqlite3_free(zClass);
  zHash1[iScope] = 0;
  memcpy(zHash2, zHash1, iScope);
  zHash2[iScope] = 'Z';
  zHash2[iScope+1] = 0;
#if SPELLFIX_MX_RUN>1
  for(i=0; i<p->nRun; i++){
    if( strcmp(p->azPrior[i], zHash1)==0 ) return;
  }
#endif
  assert( p->nRun<SPELLFIX_MX_RUN );
  memcpy(p->azPrior[p->nRun++], zHash1, iScope+1);
  if( sqlite3_bind_text(pStmt, 1, zHash1, -1, SQLITE_STATIC)==SQLITE_NOMEM
   || sqlite3_bind_text(pStmt, 2, zHash2, -1, SQLITE_STATIC)==SQLITE_NOMEM
  ){
    p->rc = SQLITE_NOMEM;
    return;
  }
#if SPELLFIX_MX_RUN>1
  for(i=0; i<pCur->nRow; i++){
    if( pCur->a[i].iScore>iWorst ){
      iWorst = pCur->a[i].iScore;
      idxWorst = i;
    }
  }
#endif
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    int iMatchlen = -1;
    iRank = sqlite3_column_int(pStmt, 2);
    if( p->pMatchStr3 ){
      int nWord = sqlite3_column_bytes(pStmt, 1);
      zWord = (const char*)sqlite3_column_text(pStmt, 1);
      iDist = editDist3Core(p->pMatchStr3, zWord, nWord, p->pLang, &iMatchlen);
    }else{
      zK1 = (const char*)sqlite3_column_text(pStmt, 3);
      if( zK1==0 ) continue;
      iDist = editdist1(p->zPattern, zK1, 0);
    }
    if( iDist<0 ){
      p->rc = SQLITE_NOMEM;
      break;
    }
    pCur->nSearch++;
    
    /* If there is a "distance < $dist" or "distance <= $dist" constraint,
    ** check if this row meets it. If not, jump back up to the top of the
    ** loop to process the next row. Otherwise, if the row does match the
    ** distance constraint, check if the pCur->a[] array is already full.
    ** If it is and no explicit "top = ?" constraint was present in the
    ** query, grow the array to ensure there is room for the new entry. */
    assert( (p->iMaxDist>=0)==((pCur->idxNum & SPELLFIX_IDXNUM_DIST) ? 1 : 0) );
    if( p->iMaxDist>=0 ){
      if( iDist>p->iMaxDist ) continue;
      if( pCur->nRow>=pCur->nAlloc && (pCur->idxNum & SPELLFIX_IDXNUM_TOP)==0 ){
        spellfix1ResizeCursor(pCur, pCur->nAlloc*2 + 10);
        if( pCur->a==0 ) break;
      }
    }

    iScore = spellfix1Score(iDist,iRank);
    if( pCur->nRow<pCur->nAlloc ){
      idx = pCur->nRow;
    }else if( iScore<iWorst ){
      idx = idxWorst;
      sqlite3_free(pCur->a[idx].zWord);
    }else{
      continue;
    }

    pCur->a[idx].zWord = sqlite3_mprintf("%s", sqlite3_column_text(pStmt, 1));
    if( pCur->a[idx].zWord==0 ){
      p->rc = SQLITE_NOMEM;
      break;
    }
    pCur->a[idx].iRowid = sqlite3_column_int64(pStmt, 0);
    pCur->a[idx].iRank = iRank;
    pCur->a[idx].iDistance = iDist;
    pCur->a[idx].iScore = iScore;
    pCur->a[idx].iMatchlen = iMatchlen;
    memcpy(pCur->a[idx].zHash, zHash1, iScope+1);
    if( pCur->nRow<pCur->nAlloc ) pCur->nRow++;
    if( pCur->nRow==pCur->nAlloc ){
      iWorst = pCur->a[0].iScore;
      idxWorst = 0;
      for(i=1; i<pCur->nRow; i++){
        iScore = pCur->a[i].iScore;
        if( iWorst<iScore ){
          iWorst = iScore;
          idxWorst = i;
        }
      }
    }
  }
  rc = sqlite3_reset(pStmt);
  if( rc ) p->rc = rc;
}