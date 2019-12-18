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
struct TYPE_3__ {scalar_t__ pCsr; scalar_t__ nTransOpen; scalar_t__ iReader; scalar_t__ bRoTrans; scalar_t__ pClient; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void assert_db_state(lsm_db *pDb){

  /* If there is at least one cursor or a write transaction open, the database
  ** handle must be holding a pointer to a client snapshot. And the reverse 
  ** - if there are no open cursors and no write transactions then there must 
  ** not be a client snapshot.  */
  
  assert( (pDb->pCsr!=0||pDb->nTransOpen>0)==(pDb->iReader>=0||pDb->bRoTrans) );

  assert( (pDb->iReader<0 && pDb->bRoTrans==0) || pDb->pClient!=0 );

  assert( pDb->nTransOpen>=0 );
}