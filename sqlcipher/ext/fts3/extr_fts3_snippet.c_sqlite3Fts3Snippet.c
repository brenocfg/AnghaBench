#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_15__ {scalar_t__ pVtab; } ;
struct TYPE_19__ {int /*<<< orphan*/  pExpr; TYPE_1__ base; } ;
struct TYPE_18__ {int nColumn; } ;
struct TYPE_17__ {int covered; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {char* z; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ StrBuffer ;
typedef  TYPE_3__ SnippetFragment ;
typedef  TYPE_4__ Fts3Table ;
typedef  TYPE_5__ Fts3Cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC (char*) ; 
 int SizeofArray (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3BestSnippet (int,TYPE_5__*,int,int,int*,TYPE_3__*,int*) ; 
 int fts3SnippetText (TYPE_5__*,TYPE_3__*,int,int,int,char const*,char const*,char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts3SegmentsClose (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/  (*) (char*)) ; 

void sqlite3Fts3Snippet(
  sqlite3_context *pCtx,          /* SQLite function call context */
  Fts3Cursor *pCsr,               /* Cursor object */
  const char *zStart,             /* Snippet start text - "<b>" */
  const char *zEnd,               /* Snippet end text - "</b>" */
  const char *zEllipsis,          /* Snippet ellipsis text - "<b>...</b>" */
  int iCol,                       /* Extract snippet from this column */
  int nToken                      /* Approximate number of tokens in snippet */
){
  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
  int rc = SQLITE_OK;
  int i;
  StrBuffer res = {0, 0, 0};

  /* The returned text includes up to four fragments of text extracted from
  ** the data in the current row. The first iteration of the for(...) loop
  ** below attempts to locate a single fragment of text nToken tokens in 
  ** size that contains at least one instance of all phrases in the query
  ** expression that appear in the current row. If such a fragment of text
  ** cannot be found, the second iteration of the loop attempts to locate
  ** a pair of fragments, and so on.
  */
  int nSnippet = 0;               /* Number of fragments in this snippet */
  SnippetFragment aSnippet[4];    /* Maximum of 4 fragments per snippet */
  int nFToken = -1;               /* Number of tokens in each fragment */

  if( !pCsr->pExpr ){
    sqlite3_result_text(pCtx, "", 0, SQLITE_STATIC);
    return;
  }

  /* Limit the snippet length to 64 tokens. */
  if( nToken<-64 ) nToken = -64;
  if( nToken>+64 ) nToken = +64;

  for(nSnippet=1; 1; nSnippet++){

    int iSnip;                    /* Loop counter 0..nSnippet-1 */
    u64 mCovered = 0;             /* Bitmask of phrases covered by snippet */
    u64 mSeen = 0;                /* Bitmask of phrases seen by BestSnippet() */

    if( nToken>=0 ){
      nFToken = (nToken+nSnippet-1) / nSnippet;
    }else{
      nFToken = -1 * nToken;
    }

    for(iSnip=0; iSnip<nSnippet; iSnip++){
      int iBestScore = -1;        /* Best score of columns checked so far */
      int iRead;                  /* Used to iterate through columns */
      SnippetFragment *pFragment = &aSnippet[iSnip];

      memset(pFragment, 0, sizeof(*pFragment));

      /* Loop through all columns of the table being considered for snippets.
      ** If the iCol argument to this function was negative, this means all
      ** columns of the FTS3 table. Otherwise, only column iCol is considered.
      */
      for(iRead=0; iRead<pTab->nColumn; iRead++){
        SnippetFragment sF = {0, 0, 0, 0};
        int iS = 0;
        if( iCol>=0 && iRead!=iCol ) continue;

        /* Find the best snippet of nFToken tokens in column iRead. */
        rc = fts3BestSnippet(nFToken, pCsr, iRead, mCovered, &mSeen, &sF, &iS);
        if( rc!=SQLITE_OK ){
          goto snippet_out;
        }
        if( iS>iBestScore ){
          *pFragment = sF;
          iBestScore = iS;
        }
      }

      mCovered |= pFragment->covered;
    }

    /* If all query phrases seen by fts3BestSnippet() are present in at least
    ** one of the nSnippet snippet fragments, break out of the loop.
    */
    assert( (mCovered&mSeen)==mCovered );
    if( mSeen==mCovered || nSnippet==SizeofArray(aSnippet) ) break;
  }

  assert( nFToken>0 );

  for(i=0; i<nSnippet && rc==SQLITE_OK; i++){
    rc = fts3SnippetText(pCsr, &aSnippet[i], 
        i, (i==nSnippet-1), nFToken, zStart, zEnd, zEllipsis, &res
    );
  }

 snippet_out:
  sqlite3Fts3SegmentsClose(pTab);
  if( rc!=SQLITE_OK ){
    sqlite3_result_error_code(pCtx, rc);
    sqlite3_free(res.z);
  }else{
    sqlite3_result_text(pCtx, res.z, -1, sqlite3_free);
  }
}