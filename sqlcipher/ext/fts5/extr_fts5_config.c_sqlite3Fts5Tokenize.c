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
struct TYPE_5__ {int /*<<< orphan*/  pTok; TYPE_1__* pTokApi; } ;
struct TYPE_4__ {int (* xTokenize ) (int /*<<< orphan*/ ,void*,int,char const*,int,int (*) (void*,int,char const*,int,int,int)) ;} ;
typedef  TYPE_2__ Fts5Config ;

/* Variables and functions */
 int SQLITE_OK ; 
 int stub1 (int /*<<< orphan*/ ,void*,int,char const*,int,int (*) (void*,int,char const*,int,int,int)) ; 

int sqlite3Fts5Tokenize(
  Fts5Config *pConfig,            /* FTS5 Configuration object */
  int flags,                      /* FTS5_TOKENIZE_* flags */
  const char *pText, int nText,   /* Text to tokenize */
  void *pCtx,                     /* Context passed to xToken() */
  int (*xToken)(void*, int, const char*, int, int, int)    /* Callback */
){
  if( pText==0 ) return SQLITE_OK;
  return pConfig->pTokApi->xTokenize(
      pConfig->pTok, pCtx, flags, pText, nText, xToken
  );
}