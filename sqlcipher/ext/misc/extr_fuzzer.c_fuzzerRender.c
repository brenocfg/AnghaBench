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
struct TYPE_4__ {int nBasis; int n; int /*<<< orphan*/ * zBasis; TYPE_2__* pRule; } ;
typedef  TYPE_1__ fuzzer_stem ;
struct TYPE_5__ {int nTo; int nFrom; int /*<<< orphan*/ * zTo; } ;
typedef  TYPE_2__ fuzzer_rule ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 char* sqlite3_realloc (char*,int) ; 

__attribute__((used)) static int fuzzerRender(
  fuzzer_stem *pStem,   /* The stem to be rendered */
  char **pzBuf,         /* Write results into this buffer.  realloc if needed */
  int *pnBuf            /* Size of the buffer */
){
  const fuzzer_rule *pRule = pStem->pRule;
  int n;                          /* Size of output term without nul-term */
  char *z;                        /* Buffer to assemble output term in */

  n = pStem->nBasis + pRule->nTo - pRule->nFrom;
  if( (*pnBuf)<n+1 ){
    (*pzBuf) = sqlite3_realloc((*pzBuf), n+100);
    if( (*pzBuf)==0 ) return SQLITE_NOMEM;
    (*pnBuf) = n+100;
  }
  n = pStem->n;
  z = *pzBuf;
  if( n<0 ){
    memcpy(z, pStem->zBasis, pStem->nBasis+1);
  }else{
    memcpy(z, pStem->zBasis, n);
    memcpy(&z[n], pRule->zTo, pRule->nTo);
    memcpy(&z[n+pRule->nTo], &pStem->zBasis[n+pRule->nFrom], 
           pStem->nBasis-n-pRule->nFrom+1);
  }

  assert( z[pStem->nBasis + pRule->nTo - pRule->nFrom]==0 );
  return SQLITE_OK;
}