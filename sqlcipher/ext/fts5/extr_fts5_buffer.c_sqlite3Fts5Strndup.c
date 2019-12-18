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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ sqlite3_malloc (int) ; 
 scalar_t__ strlen (char const*) ; 

char *sqlite3Fts5Strndup(int *pRc, const char *pIn, int nIn){
  char *zRet = 0;
  if( *pRc==SQLITE_OK ){
    if( nIn<0 ){
      nIn = (int)strlen(pIn);
    }
    zRet = (char*)sqlite3_malloc(nIn+1);
    if( zRet ){
      memcpy(zRet, pIn, nIn);
      zRet[nIn] = '\0';
    }else{
      *pRc = SQLITE_NOMEM;
    }
  }
  return zRet;
}