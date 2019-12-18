#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int p2; } ;
typedef  TYPE_1__ VdbeOp ;
struct TYPE_6__ {scalar_t__ addrExplain; int /*<<< orphan*/  pVdbe; } ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 TYPE_1__* sqlite3VdbeGetOp (int /*<<< orphan*/ ,scalar_t__) ; 

int sqlite3VdbeExplainParent(Parse *pParse){
  VdbeOp *pOp;
  if( pParse->addrExplain==0 ) return 0;
  pOp = sqlite3VdbeGetOp(pParse->pVdbe, pParse->addrExplain);
  return pOp->p2;
}