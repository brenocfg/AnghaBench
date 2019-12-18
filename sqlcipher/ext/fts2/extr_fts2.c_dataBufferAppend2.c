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
struct TYPE_4__ {scalar_t__ nData; scalar_t__ pData; } ;
typedef  TYPE_1__ DataBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferExpand (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 

__attribute__((used)) static void dataBufferAppend2(DataBuffer *pBuffer,
                              const char *pSource1, int nSource1,
                              const char *pSource2, int nSource2){
  assert( nSource1>0 && pSource1!=NULL );
  assert( nSource2>0 && pSource2!=NULL );
  dataBufferExpand(pBuffer, nSource1+nSource2);
  memcpy(pBuffer->pData+pBuffer->nData, pSource1, nSource1);
  memcpy(pBuffer->pData+pBuffer->nData+nSource1, pSource2, nSource2);
  pBuffer->nData += nSource1+nSource2;
}