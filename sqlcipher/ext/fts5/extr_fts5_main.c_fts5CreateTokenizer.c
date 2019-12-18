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
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  fts5_tokenizer ;
typedef  int /*<<< orphan*/  fts5_api ;
struct TYPE_5__ {scalar_t__ pTok; TYPE_1__* pDfltTok; } ;
struct TYPE_4__ {char* zName; void (* xDestroy ) (void*) ;scalar_t__ pNext; int /*<<< orphan*/  x; void* pUserData; } ;
typedef  TYPE_1__ Fts5TokenizerModule ;
typedef  TYPE_2__ Fts5Global ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ sqlite3_malloc64 (scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int fts5CreateTokenizer(
  fts5_api *pApi,                 /* Global context (one per db handle) */
  const char *zName,              /* Name of new function */
  void *pUserData,                /* User data for aux. function */
  fts5_tokenizer *pTokenizer,     /* Tokenizer implementation */
  void(*xDestroy)(void*)          /* Destructor for pUserData */
){
  Fts5Global *pGlobal = (Fts5Global*)pApi;
  Fts5TokenizerModule *pNew;
  sqlite3_int64 nName;            /* Size of zName and its \0 terminator */
  sqlite3_int64 nByte;            /* Bytes of space to allocate */
  int rc = SQLITE_OK;

  nName = strlen(zName) + 1;
  nByte = sizeof(Fts5TokenizerModule) + nName;
  pNew = (Fts5TokenizerModule*)sqlite3_malloc64(nByte);
  if( pNew ){
    memset(pNew, 0, (size_t)nByte);
    pNew->zName = (char*)&pNew[1];
    memcpy(pNew->zName, zName, nName);
    pNew->pUserData = pUserData;
    pNew->x = *pTokenizer;
    pNew->xDestroy = xDestroy;
    pNew->pNext = pGlobal->pTok;
    pGlobal->pTok = pNew;
    if( pNew->pNext==0 ){
      pGlobal->pDfltTok = pNew;
    }
  }else{
    rc = SQLITE_NOMEM;
  }

  return rc;
}