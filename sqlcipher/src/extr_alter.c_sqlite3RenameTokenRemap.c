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
struct TYPE_6__ {TYPE_1__* pRename; } ;
struct TYPE_5__ {void* p; struct TYPE_5__* pNext; } ;
typedef  TYPE_1__ RenameToken ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  renameTokenCheckAll (TYPE_2__*,void*) ; 

void sqlite3RenameTokenRemap(Parse *pParse, void *pTo, void *pFrom){
  RenameToken *p;
  renameTokenCheckAll(pParse, pTo);
  for(p=pParse->pRename; p; p=p->pNext){
    if( p->p==pFrom ){
      p->p = pTo;
      break;
    }
  }
}