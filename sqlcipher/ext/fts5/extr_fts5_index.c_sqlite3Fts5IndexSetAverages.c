#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {scalar_t__ rc; } ;
typedef  TYPE_1__ Fts5Index ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_AVERAGES_ROWID ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5DataWrite (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int fts5IndexReturn (TYPE_1__*) ; 

int sqlite3Fts5IndexSetAverages(Fts5Index *p, const u8 *pData, int nData){
  assert( p->rc==SQLITE_OK );
  fts5DataWrite(p, FTS5_AVERAGES_ROWID, pData, nData);
  return fts5IndexReturn(p);
}