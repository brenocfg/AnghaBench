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
typedef  scalar_t__ sqlite3_int64 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ strlen (char const*) ; 
 char* unionMalloc (int*,scalar_t__) ; 

__attribute__((used)) static char *unionStrdup(int *pRc, const char *zIn){
  char *zRet = 0;
  if( zIn ){
    sqlite3_int64 nByte = strlen(zIn) + 1;
    zRet = unionMalloc(pRc, nByte);
    if( zRet ){
      memcpy(zRet, zIn, (size_t)nByte);
    }
  }
  return zRet;
}