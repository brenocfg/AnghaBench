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
struct TYPE_3__ {scalar_t__ shmfd; int nShm; int /*<<< orphan*/  pEnv; scalar_t__* apShm; } ;
typedef  TYPE_1__ PosixFile ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  LSM_SHM_CHUNK_SIZE ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 char* posixShmFile (TYPE_1__*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int lsmPosixOsShmUnmap(lsm_file *pFile, int bDelete){
  PosixFile *p = (PosixFile *)pFile;
  if( p->shmfd>0 ){
    int i;
    for(i=0; i<p->nShm; i++){
      if( p->apShm[i] ){
        munmap(p->apShm[i], LSM_SHM_CHUNK_SIZE);
        p->apShm[i] = 0;
      }
    }
    close(p->shmfd);
    p->shmfd = 0;
    if( bDelete ){
      char *zShm = posixShmFile(p);
      if( zShm ) unlink(zShm);
      lsmFree(p->pEnv, zShm);
    }
  }
  return LSM_OK;
}