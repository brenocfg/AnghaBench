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
 int /*<<< orphan*/  LSM_CONFIG_BLOCK_SIZE ; 
 int /*<<< orphan*/  LSM_CONFIG_PAGE_SIZE ; 
 int /*<<< orphan*/  lsm_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testCompareInt (int,int,int*) ; 

__attribute__((used)) static void testPagesize(lsm_db *db, int nPgsz, int nBlksz, int *pRc){
  if( *pRc==0 ){
    int n1 = 0;
    int n2 = 0;

    lsm_config(db, LSM_CONFIG_PAGE_SIZE, &n1);
    lsm_config(db, LSM_CONFIG_BLOCK_SIZE, &n2);

    testCompareInt(n1, nPgsz, pRc);
    testCompareInt(n2, nBlksz, pRc);
  }
}