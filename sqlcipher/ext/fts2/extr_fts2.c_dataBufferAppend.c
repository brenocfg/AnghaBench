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

__attribute__((used)) static void dataBufferAppend(DataBuffer *pBuffer,
                             const char *pSource, int nSource){
  assert( nSource>0 && pSource!=NULL );
  dataBufferExpand(pBuffer, nSource);
  memcpy(pBuffer->pData+pBuffer->nData, pSource, nSource);
  pBuffer->nData += nSource;
}