#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_2__ {scalar_t__ iRowid; scalar_t__ nStr; } ;
typedef  TYPE_1__ prefixes_cursor ;

/* Variables and functions */

__attribute__((used)) static int prefixesEof(sqlite3_vtab_cursor *cur){
  prefixes_cursor *pCur = (prefixes_cursor*)cur;
  return pCur->iRowid>pCur->nStr;
}