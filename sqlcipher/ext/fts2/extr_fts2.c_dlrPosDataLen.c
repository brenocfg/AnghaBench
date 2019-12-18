#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_4__ {int nElement; int /*<<< orphan*/  pData; } ;
typedef  TYPE_1__ DLReader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dlrAtEnd (TYPE_1__*) ; 
 int getVarint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlrPosDataLen(DLReader *pReader){
  sqlite_int64 iDummy;
  int n = getVarint(pReader->pData, &iDummy);
  assert( !dlrAtEnd(pReader) );
  return pReader->nElement-n;
}