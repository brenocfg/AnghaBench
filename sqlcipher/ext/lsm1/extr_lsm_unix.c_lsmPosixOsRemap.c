#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_size; } ;
typedef  int off_t ;
typedef  int lsm_i64 ;
typedef  int /*<<< orphan*/  lsm_file ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int nMap; void* pMap; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ PosixFile ;

/* Variables and functions */
 int LSM_IOERR_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int ftruncate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 void* mmap (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int) ; 

__attribute__((used)) static int lsmPosixOsRemap(
  lsm_file *pFile, 
  lsm_i64 iMin, 
  void **ppOut,
  lsm_i64 *pnOut
){
  off_t iSz;
  int prc;
  PosixFile *p = (PosixFile *)pFile;
  struct stat buf;

  /* If the file is between 0 and 2MB in size, extend it in chunks of 256K.
  ** Thereafter, in chunks of 1MB at a time.  */
  const int aIncrSz[] = {256*1024, 1024*1024};
  int nIncrSz = aIncrSz[iMin>(2*1024*1024)];

  if( p->pMap ){
    munmap(p->pMap, p->nMap);
    *ppOut = p->pMap = 0;
    *pnOut = p->nMap = 0;
  }

  if( iMin>=0 ){
    memset(&buf, 0, sizeof(buf));
    prc = fstat(p->fd, &buf);
    if( prc!=0 ) return LSM_IOERR_BKPT;
    iSz = buf.st_size;
    if( iSz<iMin ){
      iSz = ((iMin + nIncrSz-1) / nIncrSz) * nIncrSz;
      prc = ftruncate(p->fd, iSz);
      if( prc!=0 ) return LSM_IOERR_BKPT;
    }

    p->pMap = mmap(0, iSz, PROT_READ|PROT_WRITE, MAP_SHARED, p->fd, 0);
    p->nMap = iSz;
  }

  *ppOut = p->pMap;
  *pnOut = p->nMap;
  return LSM_OK;
}