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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_3__ {int n; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ Fts5Buffer ;

/* Variables and functions */
 int sqlite3Fts5GetVarint (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static void fts5NextRowid(Fts5Buffer *pBuf, int *piOff, i64 *piRowid){
  int i = *piOff;
  if( i>=pBuf->n ){
    *piOff = -1;
  }else{
    u64 iVal;
    *piOff = i + sqlite3Fts5GetVarint(&pBuf->p[i], &iVal);
    *piRowid += iVal;
  }
}