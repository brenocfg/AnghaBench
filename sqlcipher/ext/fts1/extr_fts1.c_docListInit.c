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
struct TYPE_3__ {int nData; scalar_t__ iLastOffset; scalar_t__ iLastPos; scalar_t__ iLastColumn; int /*<<< orphan*/  iType; int /*<<< orphan*/ * pData; } ;
typedef  int /*<<< orphan*/  DocListType ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void docListInit(DocList *d, DocListType iType,
                        const char *pData, int nData){
  d->nData = nData;
  if( nData>0 ){
    d->pData = malloc(nData);
    memcpy(d->pData, pData, nData);
  } else {
    d->pData = NULL;
  }
  d->iType = iType;
  d->iLastColumn = 0;
  d->iLastPos = d->iLastOffset = 0;
}