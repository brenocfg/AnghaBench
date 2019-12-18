#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Threadset ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ Error ;

/* Variables and functions */
 int /*<<< orphan*/  join_all_threads (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  launch_thread (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_2__*) ; 
 int /*<<< orphan*/  setstoptime (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3_enable_shared_cache (int) ; 
 int /*<<< orphan*/  stress_thread_1 ; 
 int /*<<< orphan*/  stress_thread_2 ; 
 int /*<<< orphan*/  stress_thread_3 ; 
 int /*<<< orphan*/  stress_thread_4 ; 
 int /*<<< orphan*/  stress_thread_5 ; 

__attribute__((used)) static void stress1(int nMs){
  Error err = {0};
  Threadset threads = {0};

  setstoptime(&err, nMs);
  sqlite3_enable_shared_cache(1);

  launch_thread(&err, &threads, stress_thread_1, 0);
  launch_thread(&err, &threads, stress_thread_1, 0);

  launch_thread(&err, &threads, stress_thread_2, 0);
  launch_thread(&err, &threads, stress_thread_2, 0);

  launch_thread(&err, &threads, stress_thread_3, 0);
  launch_thread(&err, &threads, stress_thread_3, 0);

  launch_thread(&err, &threads, stress_thread_4, 0);
  launch_thread(&err, &threads, stress_thread_4, 0);

  launch_thread(&err, &threads, stress_thread_5, 0);
  launch_thread(&err, &threads, stress_thread_5, (void*)1);

  join_all_threads(&err, &threads);
  sqlite3_enable_shared_cache(0);

  print_and_free_err(&err);
}