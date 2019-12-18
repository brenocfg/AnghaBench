#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_11__ {int (* xNext ) (int /*<<< orphan*/ *,char const**,int*,int*,int*,int*) ;int /*<<< orphan*/  (* xClose ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ sqlite3_tokenizer_module ;
typedef  int /*<<< orphan*/  sqlite3_tokenizer_cursor ;
struct TYPE_15__ {scalar_t__ pModule; } ;
struct TYPE_10__ {scalar_t__ pVtab; } ;
struct TYPE_14__ {int /*<<< orphan*/  iLangid; int /*<<< orphan*/  pStmt; TYPE_1__ base; } ;
struct TYPE_13__ {TYPE_6__* pTokenizer; } ;
struct TYPE_12__ {int iPos; int hlmask; int iCol; } ;
typedef  int /*<<< orphan*/  StrBuffer ;
typedef  TYPE_3__ SnippetFragment ;
typedef  TYPE_4__ Fts3Table ;
typedef  TYPE_5__ Fts3Cursor ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_NOMEM ; 
 scalar_t__ SQLITE_NULL ; 
 int SQLITE_OK ; 
 int fts3SnippetShift (TYPE_4__*,int /*<<< orphan*/ ,int,char const*,int,int*,int*) ; 
 int fts3StringAppend (int /*<<< orphan*/ *,char const*,int) ; 
 int sqlite3Fts3OpenTokenizer (TYPE_6__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_column_type (int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ *,char const**,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3SnippetText(
  Fts3Cursor *pCsr,               /* FTS3 Cursor */
  SnippetFragment *pFragment,     /* Snippet to extract */
  int iFragment,                  /* Fragment number */
  int isLast,                     /* True for final fragment in snippet */
  int nSnippet,                   /* Number of tokens in extracted snippet */
  const char *zOpen,              /* String inserted before highlighted term */
  const char *zClose,             /* String inserted after highlighted term */
  const char *zEllipsis,          /* String inserted between snippets */
  StrBuffer *pOut                 /* Write output here */
){
  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
  int rc;                         /* Return code */
  const char *zDoc;               /* Document text to extract snippet from */
  int nDoc;                       /* Size of zDoc in bytes */
  int iCurrent = 0;               /* Current token number of document */
  int iEnd = 0;                   /* Byte offset of end of current token */
  int isShiftDone = 0;            /* True after snippet is shifted */
  int iPos = pFragment->iPos;     /* First token of snippet */
  u64 hlmask = pFragment->hlmask; /* Highlight-mask for snippet */
  int iCol = pFragment->iCol+1;   /* Query column to extract text from */
  sqlite3_tokenizer_module *pMod; /* Tokenizer module methods object */
  sqlite3_tokenizer_cursor *pC;   /* Tokenizer cursor open on zDoc/nDoc */
  
  zDoc = (const char *)sqlite3_column_text(pCsr->pStmt, iCol);
  if( zDoc==0 ){
    if( sqlite3_column_type(pCsr->pStmt, iCol)!=SQLITE_NULL ){
      return SQLITE_NOMEM;
    }
    return SQLITE_OK;
  }
  nDoc = sqlite3_column_bytes(pCsr->pStmt, iCol);

  /* Open a token cursor on the document. */
  pMod = (sqlite3_tokenizer_module *)pTab->pTokenizer->pModule;
  rc = sqlite3Fts3OpenTokenizer(pTab->pTokenizer, pCsr->iLangid, zDoc,nDoc,&pC);
  if( rc!=SQLITE_OK ){
    return rc;
  }

  while( rc==SQLITE_OK ){
    const char *ZDUMMY;           /* Dummy argument used with tokenizer */
    int DUMMY1 = -1;              /* Dummy argument used with tokenizer */
    int iBegin = 0;               /* Offset in zDoc of start of token */
    int iFin = 0;                 /* Offset in zDoc of end of token */
    int isHighlight = 0;          /* True for highlighted terms */

    /* Variable DUMMY1 is initialized to a negative value above. Elsewhere
    ** in the FTS code the variable that the third argument to xNext points to
    ** is initialized to zero before the first (*but not necessarily
    ** subsequent*) call to xNext(). This is done for a particular application
    ** that needs to know whether or not the tokenizer is being used for
    ** snippet generation or for some other purpose.
    **
    ** Extreme care is required when writing code to depend on this
    ** initialization. It is not a documented part of the tokenizer interface.
    ** If a tokenizer is used directly by any code outside of FTS, this
    ** convention might not be respected.  */
    rc = pMod->xNext(pC, &ZDUMMY, &DUMMY1, &iBegin, &iFin, &iCurrent);
    if( rc!=SQLITE_OK ){
      if( rc==SQLITE_DONE ){
        /* Special case - the last token of the snippet is also the last token
        ** of the column. Append any punctuation that occurred between the end
        ** of the previous token and the end of the document to the output. 
        ** Then break out of the loop. */
        rc = fts3StringAppend(pOut, &zDoc[iEnd], -1);
      }
      break;
    }
    if( iCurrent<iPos ){ continue; }

    if( !isShiftDone ){
      int n = nDoc - iBegin;
      rc = fts3SnippetShift(
          pTab, pCsr->iLangid, nSnippet, &zDoc[iBegin], n, &iPos, &hlmask
      );
      isShiftDone = 1;

      /* Now that the shift has been done, check if the initial "..." are
      ** required. They are required if (a) this is not the first fragment,
      ** or (b) this fragment does not begin at position 0 of its column. 
      */
      if( rc==SQLITE_OK ){
        if( iPos>0 || iFragment>0 ){
          rc = fts3StringAppend(pOut, zEllipsis, -1);
        }else if( iBegin ){
          rc = fts3StringAppend(pOut, zDoc, iBegin);
        }
      }
      if( rc!=SQLITE_OK || iCurrent<iPos ) continue;
    }

    if( iCurrent>=(iPos+nSnippet) ){
      if( isLast ){
        rc = fts3StringAppend(pOut, zEllipsis, -1);
      }
      break;
    }

    /* Set isHighlight to true if this term should be highlighted. */
    isHighlight = (hlmask & ((u64)1 << (iCurrent-iPos)))!=0;

    if( iCurrent>iPos ) rc = fts3StringAppend(pOut, &zDoc[iEnd], iBegin-iEnd);
    if( rc==SQLITE_OK && isHighlight ) rc = fts3StringAppend(pOut, zOpen, -1);
    if( rc==SQLITE_OK ) rc = fts3StringAppend(pOut, &zDoc[iBegin], iFin-iBegin);
    if( rc==SQLITE_OK && isHighlight ) rc = fts3StringAppend(pOut, zClose, -1);

    iEnd = iFin;
  }

  pMod->xClose(pC);
  return rc;
}