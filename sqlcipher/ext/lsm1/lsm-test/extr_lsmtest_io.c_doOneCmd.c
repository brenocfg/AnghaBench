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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ i64 ;
struct TYPE_3__ {int nWrite; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ IoContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int fdatasync (int /*<<< orphan*/ ) ; 
 scalar_t__ getNextSize (char*,char**,int*) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ safe_isdigit (char) ; 
 scalar_t__ safe_isspace (char) ; 
 int /*<<< orphan*/  testPrintError (char*,char*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int doOneCmd(
  IoContext *pCtx,
  u8 *aData,
  int pgsz,
  char *zCmd,
  char **pzOut
){
  char c;
  char *z = zCmd;

  while( safe_isspace(*z) ) z++;
  c = *z;

  if( c==0 ){
    if( pzOut ) *pzOut = z;
    return 0;
  }

  if( c=='s' || c=='S' ){
    if( pzOut ) *pzOut = &z[1];
    return fdatasync(pCtx->fd);
  }

  if( safe_isdigit(c) ){
    i64 iOff = 0;
    int nByte = 0;
    int rc = 0;
    int nPg;
    int iPg;

    nByte = (int)getNextSize(z, &z, &rc);
    if( rc || *z!='@' ) goto bad_command;
    z++;
    iOff = getNextSize(z, &z, &rc);
    if( rc || (safe_isspace(*z)==0 && *z!='\0') ) goto bad_command;
    if( pzOut ) *pzOut = z;

    nPg = (nByte+pgsz-1) / pgsz;
    lseek(pCtx->fd, (off_t)iOff, SEEK_SET);
    for(iPg=0; iPg<nPg; iPg++){
      write(pCtx->fd, aData, pgsz);
    }
    pCtx->nWrite += nByte/1024;

    return 0;
  }

 bad_command:
  testPrintError("unrecognized command: %s", zCmd);
  return 1;
}