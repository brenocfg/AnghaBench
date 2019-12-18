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
struct TYPE_2__ {char const* pInput; int nBytes; char const* pCurrent; int /*<<< orphan*/  base; scalar_t__ nTokenAllocated; scalar_t__ nTokenBytes; int /*<<< orphan*/ * zToken; scalar_t__ iToken; } ;
typedef  TYPE_1__ simple_tokenizer_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int simpleOpen(
  sqlite3_tokenizer *pTokenizer,
  const char *pInput, int nBytes,
  sqlite3_tokenizer_cursor **ppCursor
){
  simple_tokenizer_cursor *c;

  c = (simple_tokenizer_cursor *) malloc(sizeof(simple_tokenizer_cursor));
  c->pInput = pInput;
  c->nBytes = nBytes<0 ? (int) strlen(pInput) : nBytes;
  c->pCurrent = c->pInput;        /* start tokenizing at the beginning */
  c->iToken = 0;
  c->zToken = NULL;               /* no space allocated, yet. */
  c->nTokenBytes = 0;
  c->nTokenAllocated = 0;

  *ppCursor = &c->base;
  return SQLITE_OK;
}