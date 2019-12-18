#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int /*<<< orphan*/  member_0; } ;
struct event_base {int dummy; } ;
struct TYPE_10__ {struct timeval* timeout; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ redisOptions ;
struct TYPE_11__ {char* errstr; scalar_t__ err; } ;
typedef  TYPE_2__ redisAsyncContext ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_OPTIONS_SET_TCP (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  connectCallback ; 
 int /*<<< orphan*/  disconnectCallback ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 struct event_base* event_base_new () ; 
 int /*<<< orphan*/  getCallback ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  redisAsyncCommand (TYPE_2__*,int /*<<< orphan*/ ,char*,char*,...) ; 
 TYPE_2__* redisAsyncConnectWithOptions (TYPE_1__*) ; 
 int /*<<< orphan*/  redisAsyncSetConnectCallback (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisAsyncSetDisconnectCallback (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisLibeventAttach (TYPE_2__*,struct event_base*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int main (int argc, char **argv) {
    signal(SIGPIPE, SIG_IGN);
    struct event_base *base = event_base_new();
    redisOptions options = {0};
    REDIS_OPTIONS_SET_TCP(&options, "127.0.0.1", 6379);
    struct timeval tv = {0};
    tv.tv_sec = 1;
    options.timeout = &tv;


    redisAsyncContext *c = redisAsyncConnectWithOptions(&options);
    if (c->err) {
        /* Let *c leak for now... */
        printf("Error: %s\n", c->errstr);
        return 1;
    }

    redisLibeventAttach(c,base);
    redisAsyncSetConnectCallback(c,connectCallback);
    redisAsyncSetDisconnectCallback(c,disconnectCallback);
    redisAsyncCommand(c, NULL, NULL, "SET key %b", argv[argc-1], strlen(argv[argc-1]));
    redisAsyncCommand(c, getCallback, (char*)"end-1", "GET key");
    event_base_dispatch(base);
    return 0;
}