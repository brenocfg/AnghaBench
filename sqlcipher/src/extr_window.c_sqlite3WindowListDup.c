#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_6__ {struct TYPE_6__* pNextWin; } ;
typedef  TYPE_1__ Window ;

/* Variables and functions */
 TYPE_1__* sqlite3WindowDup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

Window *sqlite3WindowListDup(sqlite3 *db, Window *p){
  Window *pWin;
  Window *pRet = 0;
  Window **pp = &pRet;

  for(pWin=p; pWin; pWin=pWin->pNextWin){
    *pp = sqlite3WindowDup(db, 0, pWin);
    if( *pp==0 ) break;
    pp = &((*pp)->pNextWin);
  }

  return pRet;
}