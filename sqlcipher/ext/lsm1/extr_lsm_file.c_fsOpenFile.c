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
typedef  int /*<<< orphan*/  lsm_file ;
struct TYPE_3__ {char* zLog; char* zDb; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int LSM_OPEN_READONLY ; 
 int lsmEnvOpen (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static lsm_file *fsOpenFile(
  FileSystem *pFS,                /* File system object */
  int bReadonly,                  /* True to open this file read-only */
  int bLog,                       /* True for log, false for db */
  int *pRc                        /* IN/OUT: Error code */
){
  lsm_file *pFile = 0;
  if( *pRc==LSM_OK ){
    int flags = (bReadonly ? LSM_OPEN_READONLY : 0);
    const char *zPath = (bLog ? pFS->zLog : pFS->zDb);

    *pRc = lsmEnvOpen(pFS->pEnv, zPath, flags, &pFile);
  }
  return pFile;
}