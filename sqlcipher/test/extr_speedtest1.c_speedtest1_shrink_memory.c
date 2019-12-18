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
struct TYPE_2__ {int /*<<< orphan*/  db; scalar_t__ bMemShrink; } ;

/* Variables and functions */
 TYPE_1__ g ; 
 int /*<<< orphan*/  sqlite3_db_release_memory (int /*<<< orphan*/ ) ; 

void speedtest1_shrink_memory(void){
#if SQLITE_VERSION_NUMBER>=3007010
  if( g.bMemShrink ) sqlite3_db_release_memory(g.db);
#endif
}