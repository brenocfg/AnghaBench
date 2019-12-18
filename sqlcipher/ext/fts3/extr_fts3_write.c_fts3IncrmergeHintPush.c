#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_4__ {int n; int /*<<< orphan*/ * a; } ;
typedef  TYPE_1__ Blob ;

/* Variables and functions */
 int FTS3_VARINT_MAX ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  blobGrowBuffer (TYPE_1__*,int,int*) ; 
 scalar_t__ sqlite3Fts3PutVarint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fts3IncrmergeHintPush(
  Blob *pHint,                    /* Hint blob to append to */
  i64 iAbsLevel,                  /* First varint to store in hint */
  int nInput,                     /* Second varint to store in hint */
  int *pRc                        /* IN/OUT: Error code */
){
  blobGrowBuffer(pHint, pHint->n + 2*FTS3_VARINT_MAX, pRc);
  if( *pRc==SQLITE_OK ){
    pHint->n += sqlite3Fts3PutVarint(&pHint->a[pHint->n], iAbsLevel);
    pHint->n += sqlite3Fts3PutVarint(&pHint->a[pHint->n], (i64)nInput);
  }
}