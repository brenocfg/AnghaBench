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
struct TYPE_7__ {TYPE_1__* pDoclist; } ;
struct TYPE_6__ {scalar_t__ iType; } ;
typedef  TYPE_2__ DocListReader ;

/* Variables and functions */
 scalar_t__ DL_POSITIONS ; 
 int /*<<< orphan*/  readDocid (TYPE_2__*) ; 
 int /*<<< orphan*/  skipPositionList (TYPE_2__*) ; 

__attribute__((used)) static void skipDocument(DocListReader *pReader){
  readDocid(pReader);
  if( pReader->pDoclist->iType >= DL_POSITIONS ){
    skipPositionList(pReader);
  }
}