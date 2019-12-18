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
typedef  int /*<<< orphan*/  lsm_env ;

/* Variables and functions */
 char* lsmMalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

char *lsmMallocStrdup(lsm_env *pEnv, const char *zIn){
  int nByte;
  char *zRet;
  nByte = strlen(zIn);
  zRet = lsmMalloc(pEnv, nByte+1);
  if( zRet ){
    memcpy(zRet, zIn, nByte+1);
  }
  return zRet;
}