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
struct TYPE_3__ {scalar_t__ sectorSize; int ctrlFlags; int /*<<< orphan*/  deviceCharacteristics; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ unixFile ;
typedef  int u32 ;

/* Variables and functions */
 int F2FS_FEATURE_ATOMIC_WRITE ; 
 int /*<<< orphan*/  F2FS_IOC_GET_FEATURES ; 
 scalar_t__ SQLITE_DEFAULT_SECTOR_SIZE ; 
 int /*<<< orphan*/  SQLITE_IOCAP_BATCH_ATOMIC ; 
 int /*<<< orphan*/  SQLITE_IOCAP_POWERSAFE_OVERWRITE ; 
 int UNIXFILE_PSOW ; 
 int /*<<< orphan*/  assert (int) ; 
 int osIoctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void setDeviceCharacteristics(unixFile *pFd){
  assert( pFd->deviceCharacteristics==0 || pFd->sectorSize!=0 );
  if( pFd->sectorSize==0 ){
#if defined(__linux__) && defined(SQLITE_ENABLE_BATCH_ATOMIC_WRITE)
    int res;
    u32 f = 0;

    /* Check for support for F2FS atomic batch writes. */
    res = osIoctl(pFd->h, F2FS_IOC_GET_FEATURES, &f);
    if( res==0 && (f & F2FS_FEATURE_ATOMIC_WRITE) ){
      pFd->deviceCharacteristics = SQLITE_IOCAP_BATCH_ATOMIC;
    }
#endif /* __linux__ && SQLITE_ENABLE_BATCH_ATOMIC_WRITE */

    /* Set the POWERSAFE_OVERWRITE flag if requested. */
    if( pFd->ctrlFlags & UNIXFILE_PSOW ){
      pFd->deviceCharacteristics |= SQLITE_IOCAP_POWERSAFE_OVERWRITE;
    }

    pFd->sectorSize = SQLITE_DEFAULT_SECTOR_SIZE;
  }
}