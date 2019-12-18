#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pTokenizer; } ;
typedef  TYPE_1__ sqlite3_tokenizer_cursor ;
struct TYPE_5__ {size_t iOffset; size_t nBytes; int nTokenAllocated; char* pToken; int /*<<< orphan*/  iToken; scalar_t__ pInput; } ;
typedef  TYPE_2__ simple_tokenizer_cursor ;
typedef  int /*<<< orphan*/  simple_tokenizer ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ simpleDelim (int /*<<< orphan*/ *,unsigned char) ; 
 char* sqlite3_realloc (char*,int) ; 

__attribute__((used)) static int simpleNext(
  sqlite3_tokenizer_cursor *pCursor,  /* Cursor returned by simpleOpen */
  const char **ppToken,               /* OUT: *ppToken is the token text */
  int *pnBytes,                       /* OUT: Number of bytes in token */
  int *piStartOffset,                 /* OUT: Starting offset of token */
  int *piEndOffset,                   /* OUT: Ending offset of token */
  int *piPosition                     /* OUT: Position integer of token */
){
  simple_tokenizer_cursor *c = (simple_tokenizer_cursor *) pCursor;
  simple_tokenizer *t = (simple_tokenizer *) pCursor->pTokenizer;
  unsigned char *p = (unsigned char *)c->pInput;

  while( c->iOffset<c->nBytes ){
    int iStartOffset;

    /* Scan past delimiter characters */
    while( c->iOffset<c->nBytes && simpleDelim(t, p[c->iOffset]) ){
      c->iOffset++;
    }

    /* Count non-delimiter characters. */
    iStartOffset = c->iOffset;
    while( c->iOffset<c->nBytes && !simpleDelim(t, p[c->iOffset]) ){
      c->iOffset++;
    }

    if( c->iOffset>iStartOffset ){
      int i, n = c->iOffset-iStartOffset;
      if( n>c->nTokenAllocated ){
        char *pNew;
        c->nTokenAllocated = n+20;
        pNew = sqlite3_realloc(c->pToken, c->nTokenAllocated);
        if( !pNew ) return SQLITE_NOMEM;
        c->pToken = pNew;
      }
      for(i=0; i<n; i++){
        /* TODO(shess) This needs expansion to handle UTF-8
        ** case-insensitivity.
        */
        unsigned char ch = p[iStartOffset+i];
        c->pToken[i] = (char)((ch>='A' && ch<='Z') ? ch-'A'+'a' : ch);
      }
      *ppToken = c->pToken;
      *pnBytes = n;
      *piStartOffset = iStartOffset;
      *piEndOffset = c->iOffset;
      *piPosition = c->iToken++;

      return SQLITE_OK;
    }
  }
  return SQLITE_DONE;
}