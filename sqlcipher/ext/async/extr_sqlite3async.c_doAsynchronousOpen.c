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

/* Variables and functions */
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int SQLITE_OPEN_MAIN_JOURNAL ; 
 int SQLITE_OPEN_TEMP_JOURNAL ; 

__attribute__((used)) static int doAsynchronousOpen(int flags){
  return (flags&SQLITE_OPEN_CREATE) && (
      (flags&SQLITE_OPEN_MAIN_JOURNAL) ||
      (flags&SQLITE_OPEN_TEMP_JOURNAL) ||
      (flags&SQLITE_OPEN_DELETEONCLOSE)
  );
}