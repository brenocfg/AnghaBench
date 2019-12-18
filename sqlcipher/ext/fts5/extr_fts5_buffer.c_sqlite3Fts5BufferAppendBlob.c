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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {size_t n; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ Fts5Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert_nc (int) ; 
 scalar_t__ fts5BufferGrow (int*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 

void sqlite3Fts5BufferAppendBlob(
  int *pRc,
  Fts5Buffer *pBuf, 
  u32 nData, 
  const u8 *pData
){
  assert_nc( *pRc || nData>=0 );
  if( nData ){
    if( fts5BufferGrow(pRc, pBuf, nData) ) return;
    memcpy(&pBuf->p[pBuf->n], pData, nData);
    pBuf->n += nData;
  }
}