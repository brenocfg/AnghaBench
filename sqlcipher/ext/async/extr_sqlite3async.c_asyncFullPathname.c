#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* xFullPathname ) (TYPE_1__*,char const*,int,char*) ;scalar_t__ pAppData; } ;
typedef  TYPE_1__ sqlite3_vfs ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ strlen (char*) ; 
 int stub1 (TYPE_1__*,char const*,int,char*) ; 

__attribute__((used)) static int asyncFullPathname(
  sqlite3_vfs *pAsyncVfs, 
  const char *zPath, 
  int nPathOut,
  char *zPathOut
){
  int rc;
  sqlite3_vfs *pVfs = (sqlite3_vfs *)pAsyncVfs->pAppData;
  rc = pVfs->xFullPathname(pVfs, zPath, nPathOut, zPathOut);

  /* Because of the way intra-process file locking works, this backend
  ** needs to return a canonical path. The following block assumes the
  ** file-system uses unix style paths. 
  */
  if( rc==SQLITE_OK ){
    int i, j;
    char *z = zPathOut;
    int n = (int)strlen(z);
    while( n>1 && z[n-1]=='/' ){ n--; }
    for(i=j=0; i<n; i++){
      if( z[i]=='/' ){
        if( z[i+1]=='/' ) continue;
        if( z[i+1]=='.' && i+2<n && z[i+2]=='/' ){
          i += 1;
          continue;
        }
        if( z[i+1]=='.' && i+3<n && z[i+2]=='.' && z[i+3]=='/' ){
          while( j>0 && z[j-1]!='/' ){ j--; }
          if( j>0 ){ j--; }
          i += 2;
          continue;
        }
      }
      z[j++] = z[i];
    }
    z[j] = 0;
  }

  return rc;
}