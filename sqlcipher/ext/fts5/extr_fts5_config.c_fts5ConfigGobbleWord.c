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
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 char* fts5ConfigSkipBareword (char const*) ; 
 int fts5Dequote (char*) ; 
 scalar_t__ fts5_isopenquote (char) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc64 (scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static const char *fts5ConfigGobbleWord(
  int *pRc,                       /* IN/OUT: Error code */
  const char *zIn,                /* Buffer to gobble string/bareword from */
  char **pzOut,                   /* OUT: malloc'd buffer containing str/bw */
  int *pbQuoted                   /* OUT: Set to true if dequoting required */
){
  const char *zRet = 0;

  sqlite3_int64 nIn = strlen(zIn);
  char *zOut = sqlite3_malloc64(nIn+1);

  assert( *pRc==SQLITE_OK );
  *pbQuoted = 0;
  *pzOut = 0;

  if( zOut==0 ){
    *pRc = SQLITE_NOMEM;
  }else{
    memcpy(zOut, zIn, (size_t)(nIn+1));
    if( fts5_isopenquote(zOut[0]) ){
      int ii = fts5Dequote(zOut);
      zRet = &zIn[ii];
      *pbQuoted = 1;
    }else{
      zRet = fts5ConfigSkipBareword(zIn);
      if( zRet ){
        zOut[zRet-zIn] = '\0';
      }
    }
  }

  if( zRet==0 ){
    sqlite3_free(zOut);
  }else{
    *pzOut = zOut;
  }

  return zRet;
}