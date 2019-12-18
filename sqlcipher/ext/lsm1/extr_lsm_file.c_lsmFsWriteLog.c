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
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_6__ {int /*<<< orphan*/  fdLog; int /*<<< orphan*/  pEnv; } ;
struct TYPE_5__ {int /*<<< orphan*/  n; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ LsmString ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int lsmEnvWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lsmFsWriteLog(FileSystem *pFS, i64 iOff, LsmString *pStr){
  assert( pFS->fdLog );
  return lsmEnvWrite(pFS->pEnv, pFS->fdLog, iOff, pStr->z, pStr->n);
}