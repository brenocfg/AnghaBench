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
 int /*<<< orphan*/  check_oom (void*) ; 
 void* sqlite3_malloc (int) ; 

__attribute__((used)) static void *safe_malloc(int sz){
  void *x = sqlite3_malloc(sz>0?sz:1);
  check_oom(x);
  return x;
}