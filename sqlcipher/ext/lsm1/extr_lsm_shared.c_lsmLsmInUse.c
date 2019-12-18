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
struct TYPE_6__ {TYPE_1__* pClient; } ;
typedef  TYPE_2__ lsm_db ;
typedef  scalar_t__ i64 ;
struct TYPE_5__ {scalar_t__ iId; } ;

/* Variables and functions */
 int LSM_OK ; 
 int isInUse (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int*) ; 

int lsmLsmInUse(lsm_db *db, i64 iLsmId, int *pbInUse){
  if( db->pClient && db->pClient->iId<=iLsmId ){
    *pbInUse = 1;
    return LSM_OK;
  }
  return isInUse(db, iLsmId, 0, pbInUse);
}