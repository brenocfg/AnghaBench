#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ nPendingData; } ;
typedef  TYPE_1__ fulltext_vtab ;
struct TYPE_14__ {scalar_t__ nData; int /*<<< orphan*/  pData; } ;
struct TYPE_13__ {int nPhrase; int /*<<< orphan*/  isPrefix; int /*<<< orphan*/  nTerm; int /*<<< orphan*/  pTerm; } ;
typedef  TYPE_2__ QueryTerm ;
typedef  TYPE_3__ DataBuffer ;

/* Variables and functions */
 scalar_t__ DL_DEFAULT ; 
 scalar_t__ DL_DOCIDS ; 
 scalar_t__ DL_POSITIONS ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferDestroy (TYPE_3__*) ; 
 int /*<<< orphan*/  dataBufferInit (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  docListPhraseMerge (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,TYPE_3__*) ; 
 int termSelect (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 

__attribute__((used)) static int docListOfTerm(
  fulltext_vtab *v,   /* The full text index */
  int iColumn,        /* column to restrict to.  No restriction if >=nColumn */
  QueryTerm *pQTerm,  /* Term we are looking for, or 1st term of a phrase */
  DataBuffer *pResult /* Write the result here */
){
  DataBuffer left, right, new;
  int i, rc;

  /* No phrase search if no position info. */
  assert( pQTerm->nPhrase==0 || DL_DEFAULT!=DL_DOCIDS );

  /* This code should never be called with buffered updates. */
  assert( v->nPendingData<0 );

  dataBufferInit(&left, 0);
  rc = termSelect(v, iColumn, pQTerm->pTerm, pQTerm->nTerm, pQTerm->isPrefix,
                  0<pQTerm->nPhrase ? DL_POSITIONS : DL_DOCIDS, &left);
  if( rc ) return rc;
  for(i=1; i<=pQTerm->nPhrase && left.nData>0; i++){
    dataBufferInit(&right, 0);
    rc = termSelect(v, iColumn, pQTerm[i].pTerm, pQTerm[i].nTerm,
                    pQTerm[i].isPrefix, DL_POSITIONS, &right);
    if( rc ){
      dataBufferDestroy(&left);
      return rc;
    }
    dataBufferInit(&new, 0);
    docListPhraseMerge(left.pData, left.nData, right.pData, right.nData,
                       i<pQTerm->nPhrase ? DL_POSITIONS : DL_DOCIDS, &new);
    dataBufferDestroy(&left);
    dataBufferDestroy(&right);
    left = new;
  }
  *pResult = left;
  return SQLITE_OK;
}