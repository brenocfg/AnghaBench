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
typedef  int /*<<< orphan*/  Fts5Structure ;
typedef  int /*<<< orphan*/  Fts5Index ;

/* Variables and functions */
 int fts5IndexReturn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts5StructureRead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5StructureRelease (int /*<<< orphan*/ *) ; 

int sqlite3Fts5IndexLoadConfig(Fts5Index *p){
  Fts5Structure *pStruct;
  pStruct = fts5StructureRead(p);
  fts5StructureRelease(pStruct);
  return fts5IndexReturn(p);
}