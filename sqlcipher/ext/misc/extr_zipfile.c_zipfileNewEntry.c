#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ zFile; } ;
struct TYPE_8__ {TYPE_1__ cds; } ;
typedef  TYPE_2__ ZipfileEntry ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 TYPE_2__* sqlite3_malloc (int) ; 
 scalar_t__ sqlite3_mprintf (char*,char const*) ; 

__attribute__((used)) static ZipfileEntry *zipfileNewEntry(const char *zPath){
  ZipfileEntry *pNew;
  pNew = sqlite3_malloc(sizeof(ZipfileEntry));
  if( pNew ){
    memset(pNew, 0, sizeof(ZipfileEntry));
    pNew->cds.zFile = sqlite3_mprintf("%s", zPath);
    if( pNew->cds.zFile==0 ){
      sqlite3_free(pNew);
      pNew = 0;
    }
  }
  return pNew;
}