#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int (* xOpen ) (TYPE_3__*,char const*,int,TYPE_2__**) ;int iVersion; int (* xLanguageid ) (TYPE_2__*,int) ;int /*<<< orphan*/  (* xClose ) (TYPE_2__*) ;} ;
typedef  TYPE_1__ sqlite3_tokenizer_module ;
struct TYPE_11__ {TYPE_3__* pTokenizer; } ;
typedef  TYPE_2__ sqlite3_tokenizer_cursor ;
struct TYPE_12__ {TYPE_1__* pModule; } ;
typedef  TYPE_3__ sqlite3_tokenizer ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (TYPE_3__*,char const*,int,TYPE_2__**) ; 
 int stub2 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

int sqlite3Fts3OpenTokenizer(
  sqlite3_tokenizer *pTokenizer,
  int iLangid,
  const char *z,
  int n,
  sqlite3_tokenizer_cursor **ppCsr
){
  sqlite3_tokenizer_module const *pModule = pTokenizer->pModule;
  sqlite3_tokenizer_cursor *pCsr = 0;
  int rc;

  rc = pModule->xOpen(pTokenizer, z, n, &pCsr);
  assert( rc==SQLITE_OK || pCsr==0 );
  if( rc==SQLITE_OK ){
    pCsr->pTokenizer = pTokenizer;
    if( pModule->iVersion>=1 ){
      rc = pModule->xLanguageid(pCsr, iLangid);
      if( rc!=SQLITE_OK ){
        pModule->xClose(pCsr);
        pCsr = 0;
      }
    }
  }
  *ppCsr = pCsr;
  return rc;
}