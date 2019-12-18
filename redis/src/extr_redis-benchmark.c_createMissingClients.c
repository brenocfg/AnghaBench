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
struct TYPE_2__ {int liveclients; int numclients; int num_threads; } ;

/* Variables and functions */
 TYPE_1__ config ; 
 int /*<<< orphan*/  createClient (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void createMissingClients(client c) {
    int n = 0;
    while(config.liveclients < config.numclients) {
        int thread_id = -1;
        if (config.num_threads)
            thread_id = config.liveclients % config.num_threads;
        createClient(NULL,0,c,thread_id);

        /* Listen backlog is quite limited on most systems */
        if (++n > 64) {
            usleep(50000);
            n = 0;
        }
    }
}