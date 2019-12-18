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
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_3__ {scalar_t__ fdDb; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int lsmEnvTruncate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

int lsmFsTruncateDb(FileSystem *pFS, i64 nByte){
  if( pFS->fdDb==0 ) return LSM_OK;
  return lsmEnvTruncate(pFS->pEnv, pFS->fdDb, nByte);
}