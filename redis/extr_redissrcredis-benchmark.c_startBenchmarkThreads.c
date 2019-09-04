#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ benchmarkThread ;
struct TYPE_5__ {int num_threads; TYPE_1__** threads; } ;

/* Variables and functions */
 TYPE_3__ config ; 
 int /*<<< orphan*/  execBenchmarkThread ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void startBenchmarkThreads() {
    int i;
    for (i = 0; i < config.num_threads; i++) {
        benchmarkThread *t = config.threads[i];
        if (pthread_create(&(t->thread), NULL, execBenchmarkThread, t)){
            fprintf(stderr, "FATAL: Failed to start thread %d.\n", i);
            exit(1);
        }
    }
    for (i = 0; i < config.num_threads; i++)
        pthread_join(config.threads[i]->thread, NULL);
}