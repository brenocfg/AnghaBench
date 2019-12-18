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
typedef  int /*<<< orphan*/  client ;
struct TYPE_2__ {char* title; scalar_t__ num_threads; void* start; scalar_t__ threads; void* totlatency; int /*<<< orphan*/  el; scalar_t__ requests_finished; scalar_t__ requests_issued; } ;

/* Variables and functions */
 int /*<<< orphan*/  aeMain (int /*<<< orphan*/ ) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  createClient (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  createMissingClients (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeAllClients () ; 
 int /*<<< orphan*/  freeBenchmarkThreads () ; 
 int /*<<< orphan*/  initBenchmarkThreads () ; 
 void* mstime () ; 
 int /*<<< orphan*/  showLatencyReport () ; 
 int /*<<< orphan*/  startBenchmarkThreads () ; 

__attribute__((used)) static void benchmark(char *title, char *cmd, int len) {
    client c;

    config.title = title;
    config.requests_issued = 0;
    config.requests_finished = 0;

    if (config.num_threads) initBenchmarkThreads();

    int thread_id = config.num_threads > 0 ? 0 : -1;
    c = createClient(cmd,len,NULL,thread_id);
    createMissingClients(c);

    config.start = mstime();
    if (!config.num_threads) aeMain(config.el);
    else startBenchmarkThreads();
    config.totlatency = mstime()-config.start;

    showLatencyReport();
    freeAllClients();
    if (config.threads) freeBenchmarkThreads();
}