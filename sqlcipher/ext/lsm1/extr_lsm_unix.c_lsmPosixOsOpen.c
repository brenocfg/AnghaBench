#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_file ;
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_5__ {char const* zName; int /*<<< orphan*/  fd; int /*<<< orphan*/ * pEnv; } ;
typedef  TYPE_1__ PosixFile ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int LSM_IOERR_BKPT ; 
 int /*<<< orphan*/  LSM_IOERR_NOENT ; 
 int LSM_NOMEM ; 
 int LSM_OK ; 
 int LSM_OPEN_READONLY ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 scalar_t__ errno ; 
 int lsmErrorBkpt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsm_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* lsm_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  open (char const*,int,int) ; 

__attribute__((used)) static int lsmPosixOsOpen(
  lsm_env *pEnv,
  const char *zFile,
  int flags,
  lsm_file **ppFile
){
  int rc = LSM_OK;
  PosixFile *p;

  p = lsm_malloc(pEnv, sizeof(PosixFile));
  if( p==0 ){
    rc = LSM_NOMEM;
  }else{
    int bReadonly = (flags & LSM_OPEN_READONLY);
    int oflags = (bReadonly ? O_RDONLY : (O_RDWR|O_CREAT));
    memset(p, 0, sizeof(PosixFile));
    p->zName = zFile;
    p->pEnv = pEnv;
    p->fd = open(zFile, oflags, 0644);
    if( p->fd<0 ){
      lsm_free(pEnv, p);
      p = 0;
      if( errno==ENOENT ){
        rc = lsmErrorBkpt(LSM_IOERR_NOENT);
      }else{
        rc = LSM_IOERR_BKPT;
      }
    }
  }

  *ppFile = (lsm_file *)p;
  return rc;
}