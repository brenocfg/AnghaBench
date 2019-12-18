#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct EvalResult {scalar_t__ nUsed; scalar_t__ szSep; scalar_t__ nAlloc; char const* zSep; int /*<<< orphan*/ * z; } ;
typedef  scalar_t__ sqlite3_int64 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  memset (struct EvalResult*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 char* sqlite3_realloc64 (int /*<<< orphan*/ *,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int callback(void *pCtx, int argc, char **argv, char **colnames){
  struct EvalResult *p = (struct EvalResult*)pCtx;
  int i; 
  if( argv==0 ) return 0;
  for(i=0; i<argc; i++){
    const char *z = argv[i] ? argv[i] : "";
    size_t sz = strlen(z);
    if( (sqlite3_int64)sz+p->nUsed+p->szSep+1 > p->nAlloc ){
      char *zNew;
      p->nAlloc = p->nAlloc*2 + sz + p->szSep + 1;
      /* Using sqlite3_realloc64() would be better, but it is a recent
      ** addition and will cause a segfault if loaded by an older version
      ** of SQLite.  */
      zNew = p->nAlloc<=0x7fffffff ? sqlite3_realloc64(p->z, p->nAlloc) : 0;
      if( zNew==0 ){
        sqlite3_free(p->z);
        memset(p, 0, sizeof(*p));
        return 1;
      }
      p->z = zNew;
    }
    if( p->nUsed>0 ){
      memcpy(&p->z[p->nUsed], p->zSep, p->szSep);
      p->nUsed += p->szSep;
    }
    memcpy(&p->z[p->nUsed], z, sz);
    p->nUsed += sz;
  }
  return 0;
}