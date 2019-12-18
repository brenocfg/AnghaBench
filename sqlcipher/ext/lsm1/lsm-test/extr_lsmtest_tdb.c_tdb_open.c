#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  zLibrary; } ;
typedef  TYPE_1__ TestDb ;
struct TYPE_7__ {int (* xOpen ) (char const*,char const*,int,TYPE_1__**) ;char const* zDefaultDb; int /*<<< orphan*/  zName; } ;

/* Variables and functions */
 int ArraySize (TYPE_4__*) ; 
 TYPE_4__* aLib ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int stub1 (char const*,char const*,int,TYPE_1__**) ; 

int tdb_open(const char *zLib, const char *zDb, int bClear, TestDb **ppDb){
  int i;
  int rc = 1;
  const char *zSpec = 0;

  int nLib = 0;
  while( zLib[nLib] && zLib[nLib]!=' ' ){
    nLib++;
  }
  zSpec = &zLib[nLib];
  while( *zSpec==' ' ) zSpec++;
  if( *zSpec=='\0' ) zSpec = 0;

  for(i=0; i<ArraySize(aLib); i++){
    if( (int)strlen(aLib[i].zName)==nLib
        && 0==memcmp(zLib, aLib[i].zName, nLib) ){
      rc = aLib[i].xOpen(zSpec, (zDb ? zDb : aLib[i].zDefaultDb), bClear, ppDb);
      if( rc==0 ){
        (*ppDb)->zLibrary = aLib[i].zName;
      }
      break;
    }
  }

  if( rc ){
    /* Failed to find the requested database library. Return an error. */
    *ppDb = 0;
  }
  return rc;
}