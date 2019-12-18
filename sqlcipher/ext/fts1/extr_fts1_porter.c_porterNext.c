#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_tokenizer_cursor ;
struct TYPE_2__ {char* zInput; size_t iOffset; size_t nInput; int nAllocated; char* zToken; int /*<<< orphan*/  iToken; } ;
typedef  TYPE_1__ porter_tokenizer_cursor ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ isDelim (char const) ; 
 int /*<<< orphan*/  porter_stemmer (char const*,int,char*,int*) ; 
 char* realloc (char*,int) ; 

__attribute__((used)) static int porterNext(
  sqlite3_tokenizer_cursor *pCursor,  /* Cursor returned by porterOpen */
  const char **pzToken,               /* OUT: *pzToken is the token text */
  int *pnBytes,                       /* OUT: Number of bytes in token */
  int *piStartOffset,                 /* OUT: Starting offset of token */
  int *piEndOffset,                   /* OUT: Ending offset of token */
  int *piPosition                     /* OUT: Position integer of token */
){
  porter_tokenizer_cursor *c = (porter_tokenizer_cursor *) pCursor;
  const char *z = c->zInput;

  while( c->iOffset<c->nInput ){
    int iStartOffset, ch;

    /* Scan past delimiter characters */
    while( c->iOffset<c->nInput && isDelim(z[c->iOffset]) ){
      c->iOffset++;
    }

    /* Count non-delimiter characters. */
    iStartOffset = c->iOffset;
    while( c->iOffset<c->nInput && !isDelim(z[c->iOffset]) ){
      c->iOffset++;
    }

    if( c->iOffset>iStartOffset ){
      int n = c->iOffset-iStartOffset;
      if( n>c->nAllocated ){
        c->nAllocated = n+20;
        c->zToken = realloc(c->zToken, c->nAllocated);
        if( c->zToken==NULL ) return SQLITE_NOMEM;
      }
      porter_stemmer(&z[iStartOffset], n, c->zToken, pnBytes);
      *pzToken = c->zToken;
      *piStartOffset = iStartOffset;
      *piEndOffset = c->iOffset;
      *piPosition = c->iToken++;
      return SQLITE_OK;
    }
  }
  return SQLITE_DONE;
}