#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct BuiltinTokenizer   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fts5_tokenizer ;
struct TYPE_7__ {int (* xCreateTokenizer ) (TYPE_2__*,char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ fts5_api ;
struct BuiltinTokenizer {char const* zName; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int ArraySize (TYPE_5__*) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts5AsciiCreate ; 
 int /*<<< orphan*/  fts5AsciiDelete ; 
 int /*<<< orphan*/  fts5AsciiTokenize ; 
 int /*<<< orphan*/  fts5PorterCreate ; 
 int /*<<< orphan*/  fts5PorterDelete ; 
 int /*<<< orphan*/  fts5PorterTokenize ; 
 int /*<<< orphan*/  fts5UnicodeCreate ; 
 int /*<<< orphan*/  fts5UnicodeDelete ; 
 int /*<<< orphan*/  fts5UnicodeTokenize ; 
 int stub1 (TYPE_2__*,char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sqlite3Fts5TokenizerInit(fts5_api *pApi){
  struct BuiltinTokenizer {
    const char *zName;
    fts5_tokenizer x;
  } aBuiltin[] = {
    { "unicode61", {fts5UnicodeCreate, fts5UnicodeDelete, fts5UnicodeTokenize}},
    { "ascii",     {fts5AsciiCreate, fts5AsciiDelete, fts5AsciiTokenize }},
    { "porter",    {fts5PorterCreate, fts5PorterDelete, fts5PorterTokenize }},
  };
  
  int rc = SQLITE_OK;             /* Return code */
  int i;                          /* To iterate through builtin functions */

  for(i=0; rc==SQLITE_OK && i<ArraySize(aBuiltin); i++){
    rc = pApi->xCreateTokenizer(pApi,
        aBuiltin[i].zName,
        (void*)pApi,
        &aBuiltin[i].x,
        0
    );
  }

  return rc;
}