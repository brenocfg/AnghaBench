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
struct TYPE_3__ {char* zName; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ PosixFile ;

/* Variables and functions */
 scalar_t__ lsmMalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *posixShmFile(PosixFile *p){
  char *zShm;
  int nName = strlen(p->zName);
  zShm = (char *)lsmMalloc(p->pEnv, nName+4+1);
  if( zShm ){
    memcpy(zShm, p->zName, nName);
    memcpy(&zShm[nName], "-shm", 5);
  }
  return zShm;
}