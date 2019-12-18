#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fts5_tokenizer ;
typedef  int /*<<< orphan*/  fts5_api ;
struct TYPE_3__ {void* pUserData; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ Fts5TokenizerModule ;
typedef  int /*<<< orphan*/  Fts5Global ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 TYPE_1__* fts5LocateTokenizer (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fts5FindTokenizer(
  fts5_api *pApi,                 /* Global context (one per db handle) */
  const char *zName,              /* Name of new function */
  void **ppUserData,
  fts5_tokenizer *pTokenizer      /* Populate this object */
){
  int rc = SQLITE_OK;
  Fts5TokenizerModule *pMod;

  pMod = fts5LocateTokenizer((Fts5Global*)pApi, zName);
  if( pMod ){
    *pTokenizer = pMod->x;
    *ppUserData = pMod->pUserData;
  }else{
    memset(pTokenizer, 0, sizeof(fts5_tokenizer));
    rc = SQLITE_ERROR;
  }

  return rc;
}