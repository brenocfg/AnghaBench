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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_3__ {int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ Fts5Index ;

/* Variables and functions */
 void* sqlite3Fts5MallocZero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *fts5IdxMalloc(Fts5Index *p, sqlite3_int64 nByte){
  return sqlite3Fts5MallocZero(&p->rc, nByte);
}