#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  key; int /*<<< orphan*/  cert; int /*<<< orphan*/  ca_cert; } ;
struct config {TYPE_1__ ssl; } ;
struct TYPE_7__ {char* errstr; scalar_t__ err; } ;
typedef  TYPE_2__ redisContext ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  redisFree (TYPE_2__*) ; 
 int /*<<< orphan*/  redisSecureConnection (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_ssl_handshake(redisContext *c, struct config config) {
#ifdef HIREDIS_TEST_SSL
    redisSecureConnection(c, config.ssl.ca_cert, config.ssl.cert, config.ssl.key, NULL);
    if (c->err) {
        printf("SSL error: %s\n", c->errstr);
        redisFree(c);
        exit(1);
    }
#else
    (void) c;
    (void) config;
#endif
}