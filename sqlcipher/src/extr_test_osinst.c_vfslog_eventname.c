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

/* Variables and functions */
#define  OS_ACCESS 151 
#define  OS_ANNOTATE 150 
#define  OS_CHECKRESERVEDLOCK 149 
#define  OS_CLOSE 148 
#define  OS_CURRENTTIME 147 
#define  OS_DELETE 146 
#define  OS_DEVCHAR 145 
#define  OS_FILECONTROL 144 
#define  OS_FILESIZE 143 
#define  OS_FULLPATHNAME 142 
#define  OS_LOCK 141 
#define  OS_OPEN 140 
#define  OS_RANDOMNESS 139 
#define  OS_READ 138 
#define  OS_SECTORSIZE 137 
#define  OS_SHMBARRIER 136 
#define  OS_SHMLOCK 135 
#define  OS_SHMMAP 134 
#define  OS_SHMUNMAP 133 
#define  OS_SLEEP 132 
#define  OS_SYNC 131 
#define  OS_TRUNCATE 130 
#define  OS_UNLOCK 129 
#define  OS_WRITE 128 

__attribute__((used)) static const char *vfslog_eventname(int eEvent){
  const char *zEvent = 0;

  switch( eEvent ){
    case OS_CLOSE:             zEvent = "xClose"; break;
    case OS_READ:              zEvent = "xRead"; break;
    case OS_WRITE:             zEvent = "xWrite"; break;
    case OS_TRUNCATE:          zEvent = "xTruncate"; break;
    case OS_SYNC:              zEvent = "xSync"; break;
    case OS_FILESIZE:          zEvent = "xFilesize"; break;
    case OS_LOCK:              zEvent = "xLock"; break;
    case OS_UNLOCK:            zEvent = "xUnlock"; break;
    case OS_CHECKRESERVEDLOCK: zEvent = "xCheckResLock"; break;
    case OS_FILECONTROL:       zEvent = "xFileControl"; break;
    case OS_SECTORSIZE:        zEvent = "xSectorSize"; break;
    case OS_DEVCHAR:           zEvent = "xDeviceChar"; break;
    case OS_OPEN:              zEvent = "xOpen"; break;
    case OS_DELETE:            zEvent = "xDelete"; break;
    case OS_ACCESS:            zEvent = "xAccess"; break;
    case OS_FULLPATHNAME:      zEvent = "xFullPathname"; break;
    case OS_RANDOMNESS:        zEvent = "xRandomness"; break;
    case OS_SLEEP:             zEvent = "xSleep"; break;
    case OS_CURRENTTIME:       zEvent = "xCurrentTime"; break;

    case OS_SHMUNMAP:          zEvent = "xShmUnmap"; break;
    case OS_SHMLOCK:           zEvent = "xShmLock"; break;
    case OS_SHMBARRIER:        zEvent = "xShmBarrier"; break;
    case OS_SHMMAP:            zEvent = "xShmMap"; break;

    case OS_ANNOTATE:          zEvent = "annotation"; break;
  }

  return zEvent;
}