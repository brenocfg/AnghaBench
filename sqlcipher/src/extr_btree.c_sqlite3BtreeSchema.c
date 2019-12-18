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
struct TYPE_7__ {void* pSchema; void (* xFreeSchema ) (void*) ;} ;
struct TYPE_6__ {TYPE_2__* pBt; } ;
typedef  TYPE_1__ Btree ;
typedef  TYPE_2__ BtShared ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_1__*) ; 
 void* sqlite3DbMallocZero (int /*<<< orphan*/ ,int) ; 

void *sqlite3BtreeSchema(Btree *p, int nBytes, void(*xFree)(void *)){
  BtShared *pBt = p->pBt;
  sqlite3BtreeEnter(p);
  if( !pBt->pSchema && nBytes ){
    pBt->pSchema = sqlite3DbMallocZero(0, nBytes);
    pBt->xFreeSchema = xFree;
  }
  sqlite3BtreeLeave(p);
  return pBt->pSchema;
}