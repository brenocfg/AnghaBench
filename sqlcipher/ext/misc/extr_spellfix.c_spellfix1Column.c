#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_4__ {size_t iRow; int iLang; char* zPattern; int iTop; int iScope; int nSearch; TYPE_1__* a; scalar_t__ pFullScan; } ;
typedef  TYPE_2__ spellfix1_cursor ;
struct TYPE_3__ {char* zWord; int iRank; int iDistance; int iScore; int iMatchlen; char* zHash; } ;

/* Variables and functions */
#define  SPELLFIX_COL_DISTANCE 137 
#define  SPELLFIX_COL_LANGID 136 
#define  SPELLFIX_COL_MATCHLEN 135 
#define  SPELLFIX_COL_PHONEHASH 134 
#define  SPELLFIX_COL_RANK 133 
#define  SPELLFIX_COL_SCOPE 132 
#define  SPELLFIX_COL_SCORE 131 
#define  SPELLFIX_COL_SRCHCNT 130 
#define  SPELLFIX_COL_TOP 129 
#define  SPELLFIX_COL_WORD 128 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int editdist1 (char*,char*,int*) ; 
 int /*<<< orphan*/  sqlite3_column_value (scalar_t__,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int translen_to_charlen (char*,int,int) ; 
 scalar_t__ transliterate (unsigned char*,int) ; 
 int utf8Charlen (char*,int) ; 

__attribute__((used)) static int spellfix1Column(
  sqlite3_vtab_cursor *cur,
  sqlite3_context *ctx,
  int i
){
  spellfix1_cursor *pCur = (spellfix1_cursor*)cur;
  if( pCur->pFullScan ){
    if( i<=SPELLFIX_COL_LANGID ){
      sqlite3_result_value(ctx, sqlite3_column_value(pCur->pFullScan, i));
    }else{
      sqlite3_result_null(ctx);
    }
    return SQLITE_OK;
  }
  switch( i ){
    case SPELLFIX_COL_WORD: {
      sqlite3_result_text(ctx, pCur->a[pCur->iRow].zWord, -1, SQLITE_STATIC);
      break;
    }
    case SPELLFIX_COL_RANK: {
      sqlite3_result_int(ctx, pCur->a[pCur->iRow].iRank);
      break;
    }
    case SPELLFIX_COL_DISTANCE: {
      sqlite3_result_int(ctx, pCur->a[pCur->iRow].iDistance);
      break;
    }
    case SPELLFIX_COL_LANGID: {
      sqlite3_result_int(ctx, pCur->iLang);
      break;
    }
    case SPELLFIX_COL_SCORE: {
      sqlite3_result_int(ctx, pCur->a[pCur->iRow].iScore);
      break;
    }
    case SPELLFIX_COL_MATCHLEN: {
      int iMatchlen = pCur->a[pCur->iRow].iMatchlen;
      if( iMatchlen<0 ){
        int nPattern = (int)strlen(pCur->zPattern);
        char *zWord = pCur->a[pCur->iRow].zWord;
        int nWord = (int)strlen(zWord);

        if( nPattern>0 && pCur->zPattern[nPattern-1]=='*' ){
          char *zTranslit;
          int res;
          zTranslit = (char *)transliterate((unsigned char *)zWord, nWord);
          if( !zTranslit ) return SQLITE_NOMEM;
          res = editdist1(pCur->zPattern, zTranslit, &iMatchlen);
          sqlite3_free(zTranslit);
          if( res<0 ) return SQLITE_NOMEM;
          iMatchlen = translen_to_charlen(zWord, nWord, iMatchlen);
        }else{
          iMatchlen = utf8Charlen(zWord, nWord);
        }
      }

      sqlite3_result_int(ctx, iMatchlen);
      break;
    }
    case SPELLFIX_COL_PHONEHASH: {
      sqlite3_result_text(ctx, pCur->a[pCur->iRow].zHash, -1, SQLITE_STATIC);
      break;
    }
    case SPELLFIX_COL_TOP: {
      sqlite3_result_int(ctx, pCur->iTop);
      break;
    }
    case SPELLFIX_COL_SCOPE: {
      sqlite3_result_int(ctx, pCur->iScope);
      break;
    }
    case SPELLFIX_COL_SRCHCNT: {
      sqlite3_result_int(ctx, pCur->nSearch);
      break;
    }
    default: {
      sqlite3_result_null(ctx);
      break;
    }
  }
  return SQLITE_OK;
}