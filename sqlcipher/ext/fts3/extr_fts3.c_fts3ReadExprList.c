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
struct TYPE_3__ {int zContentTbl; int nColumn; char** azColumn; char* zDb; int zName; int /*<<< orphan*/  zLanguageid; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int /*<<< orphan*/  fts3Appendf (int*,char**,char*,...) ; 
 char* fts3QuoteId (char const*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 

__attribute__((used)) static char *fts3ReadExprList(Fts3Table *p, const char *zFunc, int *pRc){
  char *zRet = 0;
  char *zFree = 0;
  char *zFunction;
  int i;

  if( p->zContentTbl==0 ){
    if( !zFunc ){
      zFunction = "";
    }else{
      zFree = zFunction = fts3QuoteId(zFunc);
    }
    fts3Appendf(pRc, &zRet, "docid");
    for(i=0; i<p->nColumn; i++){
      fts3Appendf(pRc, &zRet, ",%s(x.'c%d%q')", zFunction, i, p->azColumn[i]);
    }
    if( p->zLanguageid ){
      fts3Appendf(pRc, &zRet, ", x.%Q", "langid");
    }
    sqlite3_free(zFree);
  }else{
    fts3Appendf(pRc, &zRet, "rowid");
    for(i=0; i<p->nColumn; i++){
      fts3Appendf(pRc, &zRet, ", x.'%q'", p->azColumn[i]);
    }
    if( p->zLanguageid ){
      fts3Appendf(pRc, &zRet, ", x.%Q", p->zLanguageid);
    }
  }
  fts3Appendf(pRc, &zRet, " FROM '%q'.'%q%s' AS x", 
      p->zDb,
      (p->zContentTbl ? p->zContentTbl : p->zName),
      (p->zContentTbl ? "" : "_content")
  );
  return zRet;
}