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
struct TYPE_2__ {int iTimeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  errorMessage (char*,int) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  sqlite3_sleep (int) ; 

__attribute__((used)) static int busyHandler(void *pCD, int count){
  UNUSED_PARAMETER(pCD);
  if( count*10>g.iTimeout ){
    if( g.iTimeout>0 ) errorMessage("timeout after %dms", g.iTimeout);
    return 0;
  }
  sqlite3_sleep(10);
  return 1;
}