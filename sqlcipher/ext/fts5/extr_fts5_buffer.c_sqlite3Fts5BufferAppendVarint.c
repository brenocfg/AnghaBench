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
struct TYPE_4__ {size_t n; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ Fts5Buffer ;

/* Variables and functions */
 scalar_t__ fts5BufferGrow (int*,TYPE_1__*,int) ; 
 scalar_t__ sqlite3Fts5PutVarint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3Fts5BufferAppendVarint(int *pRc, Fts5Buffer *pBuf, i64 iVal){
  if( fts5BufferGrow(pRc, pBuf, 9) ) return;
  pBuf->n += sqlite3Fts5PutVarint(&pBuf->p[pBuf->n], iVal);
}