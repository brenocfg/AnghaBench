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
struct TYPE_2__ {int requests; int /*<<< orphan*/  liveclients_mutex; scalar_t__ num_threads; int /*<<< orphan*/  liveclients; scalar_t__ keepalive; scalar_t__ el; int /*<<< orphan*/  requests_finished; } ;

/* Variables and functions */
 int /*<<< orphan*/  aeStop (scalar_t__) ; 
 int /*<<< orphan*/  atomicGet (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  createMissingClients (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeClient (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resetClient (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clientDone(client c) {
    int requests_finished = 0;
    atomicGet(config.requests_finished, requests_finished);
    if (requests_finished >= config.requests) {
        freeClient(c);
        if (!config.num_threads && config.el) aeStop(config.el);
        return;
    }
    if (config.keepalive) {
        resetClient(c);
    } else {
        if (config.num_threads) pthread_mutex_lock(&(config.liveclients_mutex));
        config.liveclients--;
        createMissingClients(c);
        config.liveclients++;
        if (config.num_threads)
            pthread_mutex_unlock(&(config.liveclients_mutex));
        freeClient(c);
    }
}