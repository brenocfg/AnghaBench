#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {int /*<<< orphan*/  ai_family; } ;
struct TYPE_5__ {scalar_t__ err; int /*<<< orphan*/  errstr; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ REDIS_ERR_IO ; 
 scalar_t__ REDIS_ERR_OTHER ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__* redisConnect (char*,int) ; 
 TYPE_1__* redisConnectUnix (char*) ; 
 int /*<<< orphan*/  redisFree (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test (char*) ; 
 int /*<<< orphan*/  test_cond (int) ; 

__attribute__((used)) static void test_blocking_connection_errors(void) {
    redisContext *c;
    struct addrinfo hints = {.ai_family = AF_INET};
    struct addrinfo *ai_tmp = NULL;
    const char *bad_domain = "idontexist.com";

    int rv = getaddrinfo(bad_domain, "6379", &hints, &ai_tmp);
    if (rv != 0) {
        // Address does *not* exist
        test("Returns error when host cannot be resolved: ");
        // First see if this domain name *actually* resolves to NXDOMAIN
        c = redisConnect("dontexist.com", 6379);
        test_cond(
            c->err == REDIS_ERR_OTHER &&
            (strcmp(c->errstr, "Name or service not known") == 0 ||
             strcmp(c->errstr, "Can't resolve: sadkfjaskfjsa.com") == 0 ||
             strcmp(c->errstr,
                    "nodename nor servname provided, or not known") == 0 ||
             strcmp(c->errstr, "No address associated with hostname") == 0 ||
             strcmp(c->errstr, "Temporary failure in name resolution") == 0 ||
             strcmp(c->errstr,
                    "hostname nor servname provided, or not known") == 0 ||
             strcmp(c->errstr, "no address associated with name") == 0));
        redisFree(c);
    } else {
        printf("Skipping NXDOMAIN test. Found evil ISP!\n");
        freeaddrinfo(ai_tmp);
    }

    test("Returns error when the port is not open: ");
    c = redisConnect((char*)"localhost", 1);
    test_cond(c->err == REDIS_ERR_IO &&
        strcmp(c->errstr,"Connection refused") == 0);
    redisFree(c);

    test("Returns error when the unix_sock socket path doesn't accept connections: ");
    c = redisConnectUnix((char*)"/tmp/idontexist.sock");
    test_cond(c->err == REDIS_ERR_IO); /* Don't care about the message... */
    redisFree(c);
}