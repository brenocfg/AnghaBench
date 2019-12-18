#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* pFirstEntry; } ;
typedef  TYPE_1__ ZipfileTab ;
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
typedef  TYPE_2__ ZipfileEntry ;

/* Variables and functions */
 int /*<<< orphan*/  zipfileEntryFree (TYPE_2__*) ; 

__attribute__((used)) static void zipfileRemoveEntryFromList(ZipfileTab *pTab, ZipfileEntry *pOld){
  if( pOld ){
    ZipfileEntry **pp;
    for(pp=&pTab->pFirstEntry; (*pp)!=pOld; pp=&((*pp)->pNext));
    *pp = (*pp)->pNext;
    zipfileEntryFree(pOld);
  }
}