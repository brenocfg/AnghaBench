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
typedef  int /*<<< orphan*/  sqlite3_tokenizer ;
struct TYPE_2__ {char const* zInput; int nInput; int /*<<< orphan*/  base; scalar_t__ nAllocated; int /*<<< orphan*/ * zToken; scalar_t__ iToken; scalar_t__ iOffset; } ;
typedef  TYPE_1__ porter_tokenizer_cursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ sqlite3_malloc (int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int porterOpen(
  sqlite3_tokenizer *pTokenizer,         /* The tokenizer */
  const char *zInput, int nInput,        /* String to be tokenized */
  sqlite3_tokenizer_cursor **ppCursor    /* OUT: Tokenization cursor */
){
  porter_tokenizer_cursor *c;

  c = (porter_tokenizer_cursor *) sqlite3_malloc(sizeof(*c));
  if( c==NULL ) return SQLITE_NOMEM;

  c->zInput = zInput;
  if( zInput==0 ){
    c->nInput = 0;
  }else if( nInput<0 ){
    c->nInput = (int)strlen(zInput);
  }else{
    c->nInput = nInput;
  }
  c->iOffset = 0;                 /* start tokenizing at the beginning */
  c->iToken = 0;
  c->zToken = NULL;               /* no space allocated, yet. */
  c->nAllocated = 0;

  *ppCursor = &c->base;
  return SQLITE_OK;
}