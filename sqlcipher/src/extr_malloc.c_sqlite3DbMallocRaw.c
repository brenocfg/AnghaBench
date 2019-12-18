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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  MEMTYPE_HEAP ; 
 void* sqlite3DbMallocRawNN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* sqlite3Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3MemdebugSetType (void*,int /*<<< orphan*/ ) ; 

void *sqlite3DbMallocRaw(sqlite3 *db, u64 n){
  void *p;
  if( db ) return sqlite3DbMallocRawNN(db, n);
  p = sqlite3Malloc(n);
  sqlite3MemdebugSetType(p, MEMTYPE_HEAP);
  return p;
}