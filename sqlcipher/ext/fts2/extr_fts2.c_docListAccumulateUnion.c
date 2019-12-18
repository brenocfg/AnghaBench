#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nData; int /*<<< orphan*/  pData; } ;
typedef  TYPE_1__ DataBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  dataBufferDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  dataBufferInit (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  docListUnion (int /*<<< orphan*/ ,scalar_t__,char const*,int,TYPE_1__*) ; 

__attribute__((used)) static void docListAccumulateUnion(DataBuffer *acc,
                                   const char *pData, int nData) {
  DataBuffer tmp = *acc;
  dataBufferInit(acc, tmp.nData+nData);
  docListUnion(tmp.pData, tmp.nData, pData, nData, acc);
  dataBufferDestroy(&tmp);
}