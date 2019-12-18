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
struct TYPE_2__ {int /*<<< orphan*/  pContext; int /*<<< orphan*/  (* xDestructor ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ RtreeGeomCallback ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtreeFreeCallback(void *p){
  RtreeGeomCallback *pInfo = (RtreeGeomCallback*)p;
  if( pInfo->xDestructor ) pInfo->xDestructor(pInfo->pContext);
  sqlite3_free(p);
}