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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  Fts5Structure ;
typedef  int /*<<< orphan*/  Fts5Index ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_AVERAGES_ROWID ; 
 int /*<<< orphan*/  fts5DataWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int fts5IndexReturn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5StructureInvalidate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5StructureWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int sqlite3Fts5IndexReinit(Fts5Index *p){
  Fts5Structure s;
  fts5StructureInvalidate(p);
  memset(&s, 0, sizeof(Fts5Structure));
  fts5DataWrite(p, FTS5_AVERAGES_ROWID, (const u8*)"", 0);
  fts5StructureWrite(p, &s);
  return fts5IndexReturn(p);
}