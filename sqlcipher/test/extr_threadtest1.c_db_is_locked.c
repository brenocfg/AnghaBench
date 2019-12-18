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
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  usleep (int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int db_is_locked(void *NotUsed, int iCount){
  /* sched_yield(); */
  if( verbose ) printf("BUSY %s #%d\n", (char*)NotUsed, iCount);
  usleep(100);
  return iCount<25;
}