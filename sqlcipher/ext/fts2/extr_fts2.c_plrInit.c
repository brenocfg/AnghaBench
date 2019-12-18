#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  iType; } ;
struct TYPE_8__ {scalar_t__ iEndOffset; scalar_t__ iStartOffset; scalar_t__ iPosition; scalar_t__ iColumn; int /*<<< orphan*/  iType; int /*<<< orphan*/  nData; int /*<<< orphan*/  pData; } ;
typedef  TYPE_1__ PLReader ;
typedef  TYPE_2__ DLReader ;

/* Variables and functions */
 int /*<<< orphan*/  dlrPosData (TYPE_2__*) ; 
 int /*<<< orphan*/  dlrPosDataLen (TYPE_2__*) ; 
 int /*<<< orphan*/  plrStep (TYPE_1__*) ; 

__attribute__((used)) static void plrInit(PLReader *pReader, DLReader *pDLReader){
  pReader->pData = dlrPosData(pDLReader);
  pReader->nData = dlrPosDataLen(pDLReader);
  pReader->iType = pDLReader->iType;
  pReader->iColumn = 0;
  pReader->iPosition = 0;
  pReader->iStartOffset = 0;
  pReader->iEndOffset = 0;
  plrStep(pReader);
}