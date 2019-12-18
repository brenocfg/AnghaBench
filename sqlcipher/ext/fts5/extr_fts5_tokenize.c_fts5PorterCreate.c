#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* xFindTokenizer ) (TYPE_1__*,char const*,void**,TYPE_4__*) ;} ;
typedef  TYPE_1__ fts5_api ;
struct TYPE_8__ {int (* xCreate ) (void*,char const**,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  pTokenizer; TYPE_4__ tokenizer; } ;
typedef  TYPE_2__ PorterTokenizer ;
typedef  int /*<<< orphan*/  Fts5Tokenizer ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts5PorterDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_malloc (int) ; 
 int stub1 (TYPE_1__*,char const*,void**,TYPE_4__*) ; 
 int stub2 (void*,char const**,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5PorterCreate(
  void *pCtx, 
  const char **azArg, int nArg,
  Fts5Tokenizer **ppOut
){
  fts5_api *pApi = (fts5_api*)pCtx;
  int rc = SQLITE_OK;
  PorterTokenizer *pRet;
  void *pUserdata = 0;
  const char *zBase = "unicode61";

  if( nArg>0 ){
    zBase = azArg[0];
  }

  pRet = (PorterTokenizer*)sqlite3_malloc(sizeof(PorterTokenizer));
  if( pRet ){
    memset(pRet, 0, sizeof(PorterTokenizer));
    rc = pApi->xFindTokenizer(pApi, zBase, &pUserdata, &pRet->tokenizer);
  }else{
    rc = SQLITE_NOMEM;
  }
  if( rc==SQLITE_OK ){
    int nArg2 = (nArg>0 ? nArg-1 : 0);
    const char **azArg2 = (nArg2 ? &azArg[1] : 0);
    rc = pRet->tokenizer.xCreate(pUserdata, azArg2, nArg2, &pRet->pTokenizer);
  }

  if( rc!=SQLITE_OK ){
    fts5PorterDelete((Fts5Tokenizer*)pRet);
    pRet = 0;
  }
  *ppOut = (Fts5Tokenizer*)pRet;
  return rc;
}