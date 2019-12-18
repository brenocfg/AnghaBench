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
struct TYPE_6__ {scalar_t__ rc; } ;
typedef  TYPE_1__ Fts5Index ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5CloseReader (TYPE_1__*) ; 
 int /*<<< orphan*/  fts5IndexFlush (TYPE_1__*) ; 
 int fts5IndexReturn (TYPE_1__*) ; 

int sqlite3Fts5IndexSync(Fts5Index *p){
  assert( p->rc==SQLITE_OK );
  fts5IndexFlush(p);
  fts5CloseReader(p);
  return fts5IndexReturn(p);
}