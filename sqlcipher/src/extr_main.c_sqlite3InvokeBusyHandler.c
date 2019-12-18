#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_3__ {int (* xBusyHandler ) (void*,int) ;scalar_t__ nBusy; void* pBusyArg; scalar_t__ bExtraFileArg; } ;
typedef  TYPE_1__ BusyHandler ;

/* Variables and functions */
 int stub1 (void*,int) ; 

int sqlite3InvokeBusyHandler(BusyHandler *p, sqlite3_file *pFile){
  int rc;
  if( p->xBusyHandler==0 || p->nBusy<0 ) return 0;
  if( p->bExtraFileArg ){
    /* Add an extra parameter with the pFile pointer to the end of the
    ** callback argument list */
    int (*xTra)(void*,int,sqlite3_file*);
    xTra = (int(*)(void*,int,sqlite3_file*))p->xBusyHandler;
    rc = xTra(p->pBusyArg, p->nBusy, pFile);
  }else{
    /* Legacy style busy handler callback */
    rc = p->xBusyHandler(p->pBusyArg, p->nBusy);
  }
  if( rc==0 ){
    p->nBusy = -1;
  }else{
    p->nBusy++;
  }
  return rc; 
}