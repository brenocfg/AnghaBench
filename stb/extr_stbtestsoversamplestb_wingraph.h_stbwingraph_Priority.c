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
 int /*<<< orphan*/  GetCurrentThread () ; 
 int /*<<< orphan*/  SetThreadPriority (int /*<<< orphan*/ ,int) ; 
 int THREAD_PRIORITY_ABOVE_NORMAL ; 
 int THREAD_PRIORITY_BELOW_NORMAL ; 
 int THREAD_PRIORITY_HIGHEST ; 
 int THREAD_PRIORITY_LOWEST ; 
 int THREAD_PRIORITY_NORMAL ; 

void stbwingraph_Priority(int n)
{
   int p;
   switch (n) {
      case -1: p = THREAD_PRIORITY_BELOW_NORMAL; break;
      case 0: p = THREAD_PRIORITY_NORMAL; break;
      case 1: p = THREAD_PRIORITY_ABOVE_NORMAL; break;
      default:
         if (n < 0) p = THREAD_PRIORITY_LOWEST;
         else p = THREAD_PRIORITY_HIGHEST;
   }
   SetThreadPriority(GetCurrentThread(), p);
}