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
 int atoi (char*) ; 
 int cpu_count () ; 
 char* getenv (char*) ; 

__attribute__((used)) static int
worker_count()
{
  char *e = getenv("STRM_WORKER_MAX");
  int n;

  if (e) {
    n = atoi(e);
    if (n > 0) return n;
  }
  return cpu_count();
}