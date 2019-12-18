#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ sqlite3_int64 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* sqlite3_malloc64 (scalar_t__) ; 

__attribute__((used)) static void *fuzzMalloc(sqlite3_int64 nByte){
  void *pRet = sqlite3_malloc64(nByte);
  if( pRet ){
    memset(pRet, 0, (size_t)nByte);
  }
  return pRet;
}