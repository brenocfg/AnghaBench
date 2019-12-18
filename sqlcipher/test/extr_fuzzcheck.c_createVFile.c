#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sz; void* a; scalar_t__ nRef; void* zFilename; } ;
typedef  TYPE_1__ VFile ;
struct TYPE_6__ {TYPE_1__* aFile; } ;

/* Variables and functions */
 int MX_FILE ; 
 TYPE_1__* findVFile (char const*) ; 
 TYPE_2__ g ; 
 int /*<<< orphan*/  memcpy (void*,...) ; 
 void* safe_realloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static VFile *createVFile(const char *zName, int sz, unsigned char *pData){
  VFile *pNew = findVFile(zName);
  int i;
  if( pNew ) return pNew;
  for(i=0; i<MX_FILE && g.aFile[i].sz>=0; i++){}
  if( i>=MX_FILE ) return 0;
  pNew = &g.aFile[i];
  if( zName ){
    int nName = (int)strlen(zName)+1;
    pNew->zFilename = safe_realloc(0, nName);
    memcpy(pNew->zFilename, zName, nName);
  }else{
    pNew->zFilename = 0;
  }
  pNew->nRef = 0;
  pNew->sz = sz;
  pNew->a = safe_realloc(0, sz);
  if( sz>0 ) memcpy(pNew->a, pData, sz);
  return pNew;
}