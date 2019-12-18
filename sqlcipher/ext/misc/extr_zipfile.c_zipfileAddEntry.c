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
struct TYPE_6__ {TYPE_2__* pFirstEntry; TYPE_2__* pLastEntry; } ;
typedef  TYPE_1__ ZipfileTab ;
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
typedef  TYPE_2__ ZipfileEntry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void zipfileAddEntry(
  ZipfileTab *pTab, 
  ZipfileEntry *pBefore, 
  ZipfileEntry *pNew
){
  assert( (pTab->pFirstEntry==0)==(pTab->pLastEntry==0) );
  assert( pNew->pNext==0 );
  if( pBefore==0 ){
    if( pTab->pFirstEntry==0 ){
      pTab->pFirstEntry = pTab->pLastEntry = pNew;
    }else{
      assert( pTab->pLastEntry->pNext==0 );
      pTab->pLastEntry->pNext = pNew;
      pTab->pLastEntry = pNew;
    }
  }else{
    ZipfileEntry **pp;
    for(pp=&pTab->pFirstEntry; *pp!=pBefore; pp=&((*pp)->pNext));
    pNew->pNext = pBefore;
    *pp = pNew;
  }
}