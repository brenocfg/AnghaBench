#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {scalar_t__ iId; } ;
struct TYPE_7__ {int /*<<< orphan*/  pCtx; int /*<<< orphan*/  (* xFactory ) (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ;} ;
struct TYPE_8__ {int bInFactory; TYPE_1__ compress; TYPE_2__ factory; } ;
typedef  TYPE_3__ lsm_db ;

/* Variables and functions */
 scalar_t__ LSM_COMPRESSION_EMPTY ; 
 int LSM_MISMATCH ; 
 int LSM_OK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 

int lsmCheckCompressionId(lsm_db *pDb, u32 iReq){
  if( iReq!=LSM_COMPRESSION_EMPTY && pDb->compress.iId!=iReq ){
    if( pDb->factory.xFactory ){
      pDb->bInFactory = 1;
      pDb->factory.xFactory(pDb->factory.pCtx, pDb, iReq);
      pDb->bInFactory = 0;
    }
    if( pDb->compress.iId!=iReq ){
      /* Incompatible */
      return LSM_MISMATCH;
    }
  }
  /* Compatible */
  return LSM_OK;
}