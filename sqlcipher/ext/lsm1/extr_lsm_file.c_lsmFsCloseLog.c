#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* pFS; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_5__ {scalar_t__ fdLog; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int /*<<< orphan*/  lsmEnvClose (int /*<<< orphan*/ ,scalar_t__) ; 

void lsmFsCloseLog(lsm_db *db){
  FileSystem *pFS = db->pFS;
  if( pFS->fdLog ){
    lsmEnvClose(pFS->pEnv, pFS->fdLog);
    pFS->fdLog = 0;
  }
}