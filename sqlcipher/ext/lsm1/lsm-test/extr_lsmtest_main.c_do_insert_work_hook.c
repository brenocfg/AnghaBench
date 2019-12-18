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
 int /*<<< orphan*/  LSM_INFO_DB_STRUCTURE ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsm_free (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lsm_get_env (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsm_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  unused_parameter (void*) ; 

__attribute__((used)) static void do_insert_work_hook(lsm_db *db, void *p){
  char *z = 0;
  lsm_info(db, LSM_INFO_DB_STRUCTURE, &z);
  if( z ){
    printf("%s\n", z);
    fflush(stdout);
    lsm_free(lsm_get_env(db), z);
  }

  unused_parameter(p);
}