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
struct skynet_context {int dummy; } ;
struct skynet_config {char* logservice; scalar_t__ daemon; int /*<<< orphan*/  thread; int /*<<< orphan*/  bootstrap; int /*<<< orphan*/  logger; int /*<<< orphan*/  profile; int /*<<< orphan*/  module_path; int /*<<< orphan*/  harbor; } ;
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/ * sa_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  bootstrap (struct skynet_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  daemon_exit (scalar_t__) ; 
 scalar_t__ daemon_init (scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  handle_hup ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skynet_context_handle (struct skynet_context*) ; 
 struct skynet_context* skynet_context_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_handle_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_handle_namehandle (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skynet_harbor_exit () ; 
 int /*<<< orphan*/  skynet_harbor_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_module_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_mq_init () ; 
 int /*<<< orphan*/  skynet_profile_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_socket_free () ; 
 int /*<<< orphan*/  skynet_socket_init () ; 
 int /*<<< orphan*/  skynet_timer_init () ; 
 int /*<<< orphan*/  start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void 
skynet_start(struct skynet_config * config) {
	// register SIGHUP for log file reopen
	struct sigaction sa;
	sa.sa_handler = &handle_hup;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);
	sigaction(SIGHUP, &sa, NULL);

	if (config->daemon) {
		if (daemon_init(config->daemon)) {
			exit(1);
		}
	}
	skynet_harbor_init(config->harbor);
	skynet_handle_init(config->harbor);
	skynet_mq_init();
	skynet_module_init(config->module_path);
	skynet_timer_init();
	skynet_socket_init();
	skynet_profile_enable(config->profile);

	struct skynet_context *ctx = skynet_context_new(config->logservice, config->logger);
	if (ctx == NULL) {
		fprintf(stderr, "Can't launch %s service\n", config->logservice);
		exit(1);
	}

	skynet_handle_namehandle(skynet_context_handle(ctx), "logger");

	bootstrap(ctx, config->bootstrap);

	start(config->thread);

	// harbor_exit may call socket send, so it should exit before socket_free
	skynet_harbor_exit();
	skynet_socket_free();
	if (config->daemon) {
		daemon_exit(config->daemon);
	}
}