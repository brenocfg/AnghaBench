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
struct TYPE_3__ {int nData; int /*<<< orphan*/  pOut; scalar_t__ iOff; scalar_t__ bLog; } ;
typedef  TYPE_1__ InsertWriteHook ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 

__attribute__((used)) static void flushHook(InsertWriteHook *pHook){
  if( pHook->nData ){
    fprintf(pHook->pOut, "write %s %d %d\n", 
        (pHook->bLog ? "log" : "db"), (int)pHook->iOff, pHook->nData
    );
    pHook->nData = 0;
    fflush(pHook->pOut);
  }
}