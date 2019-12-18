#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_2__ {scalar_t__ iValue; scalar_t__ mnValue; scalar_t__ mxValue; scalar_t__ isDesc; } ;
typedef  TYPE_1__ series_cursor ;

/* Variables and functions */

__attribute__((used)) static int seriesEof(sqlite3_vtab_cursor *cur){
  series_cursor *pCur = (series_cursor*)cur;
  if( pCur->isDesc ){
    return pCur->iValue < pCur->mnValue;
  }else{
    return pCur->iValue > pCur->mxValue;
  }
}