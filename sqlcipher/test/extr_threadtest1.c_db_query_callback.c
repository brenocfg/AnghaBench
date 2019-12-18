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
struct QueryResult {int nElem; int nAlloc; char* zFile; int /*<<< orphan*/ * azElem; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int db_query_callback(
  void *pUser,     /* Pointer to the QueryResult structure */
  int nArg,        /* Number of columns in this result row */
  char **azArg,    /* Text of data in all columns */
  char **NotUsed   /* Names of the columns */
){
  struct QueryResult *pResult = (struct QueryResult*)pUser;
  int i;
  if( pResult->nElem + nArg >= pResult->nAlloc ){
    if( pResult->nAlloc==0 ){
      pResult->nAlloc = nArg+1;
    }else{
      pResult->nAlloc = pResult->nAlloc*2 + nArg + 1;
    }
    pResult->azElem = realloc( pResult->azElem, pResult->nAlloc*sizeof(char*));
    if( pResult->azElem==0 ){
      fprintf(stdout,"%s: malloc failed\n", pResult->zFile);
      return 1;
    }
  }
  if( azArg==0 ) return 0;
  for(i=0; i<nArg; i++){
    pResult->azElem[pResult->nElem++] =
        sqlite3_mprintf("%s",azArg[i] ? azArg[i] : ""); 
  }
  return 0;
}