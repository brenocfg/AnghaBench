#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct Builtin   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fts5_extension_function ;
struct TYPE_5__ {int (* xCreateFunction ) (TYPE_1__*,char const*,void*,int /*<<< orphan*/ ,void (*) (void*)) ;} ;
typedef  TYPE_1__ fts5_api ;
struct Builtin {char const* zFunc; void* pUserData; int /*<<< orphan*/  xFunc; void (* xDestroy ) (void*) ;} ;

/* Variables and functions */
 int ArraySize (TYPE_4__*) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts5Bm25Function ; 
 int /*<<< orphan*/  fts5HighlightFunction ; 
 int /*<<< orphan*/  fts5SnippetFunction ; 
 int stub1 (TYPE_1__*,char const*,void*,int /*<<< orphan*/ ,void (*) (void*)) ; 

int sqlite3Fts5AuxInit(fts5_api *pApi){
  struct Builtin {
    const char *zFunc;            /* Function name (nul-terminated) */
    void *pUserData;              /* User-data pointer */
    fts5_extension_function xFunc;/* Callback function */
    void (*xDestroy)(void*);      /* Destructor function */
  } aBuiltin [] = {
    { "snippet",   0, fts5SnippetFunction, 0 },
    { "highlight", 0, fts5HighlightFunction, 0 },
    { "bm25",      0, fts5Bm25Function,    0 },
  };
  int rc = SQLITE_OK;             /* Return code */
  int i;                          /* To iterate through builtin functions */

  for(i=0; rc==SQLITE_OK && i<ArraySize(aBuiltin); i++){
    rc = pApi->xCreateFunction(pApi,
        aBuiltin[i].zFunc,
        aBuiltin[i].pUserData,
        aBuiltin[i].xFunc,
        aBuiltin[i].xDestroy
    );
  }

  return rc;
}