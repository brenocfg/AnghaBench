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
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ sqlite3_malloc64 (size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *rbuStrndup(const char *zStr, int *pRc){
  char *zRet = 0;

  assert( *pRc==SQLITE_OK );
  if( zStr ){
    size_t nCopy = strlen(zStr) + 1;
    zRet = (char*)sqlite3_malloc64(nCopy);
    if( zRet ){
      memcpy(zRet, zStr, nCopy);
    }else{
      *pRc = SQLITE_NOMEM;
    }
  }

  return zRet;
}