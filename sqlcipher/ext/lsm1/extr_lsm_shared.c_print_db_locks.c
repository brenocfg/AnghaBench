#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_db ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int shmLockType (int /*<<< orphan*/ *,int) ; 

void print_db_locks(lsm_db *db){
  int iLock;
  for(iLock=0; iLock<16; iLock++){
    int bOne = 0;
    const char *azLock[] = {0, "shared", "exclusive"};
    const char *azName[] = {
      0, "dms1", "dms2", "writer", "worker", "checkpointer",
      "reader0", "reader1", "reader2", "reader3", "reader4", "reader5"
    };
    int eHave = shmLockType(db, iLock);
    if( azLock[eHave] ){
      printf("%s(%s on %s)", (bOne?" ":""), azLock[eHave], azName[iLock]);
      bOne = 1;
    }
  }
  printf("\n");
}