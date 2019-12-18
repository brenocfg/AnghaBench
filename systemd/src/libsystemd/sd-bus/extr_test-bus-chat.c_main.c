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
typedef  int /*<<< orphan*/  sd_bus ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  LOG_INFO ; 
 scalar_t__ PTR_TO_INT (void*) ; 
 int /*<<< orphan*/  client1 ; 
 int /*<<< orphan*/  client2 ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int log_tests_skipped (char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 int server (int /*<<< orphan*/ *) ; 
 int server_init (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        pthread_t c1, c2;
        sd_bus *bus;
        void *p;
        int q, r;

        test_setup_logging(LOG_INFO);

        r = server_init(&bus);
        if (r < 0)
                return log_tests_skipped("Failed to connect to bus");

        log_info("Initialized...");

        r = pthread_create(&c1, NULL, client1, bus);
        if (r != 0)
                return EXIT_FAILURE;

        r = pthread_create(&c2, NULL, client2, bus);
        if (r != 0)
                return EXIT_FAILURE;

        r = server(bus);

        q = pthread_join(c1, &p);
        if (q != 0)
                return EXIT_FAILURE;
        if (PTR_TO_INT(p) < 0)
                return EXIT_FAILURE;

        q = pthread_join(c2, &p);
        if (q != 0)
                return EXIT_FAILURE;
        if (PTR_TO_INT(p) < 0)
                return EXIT_FAILURE;

        if (r < 0)
                return EXIT_FAILURE;

        return EXIT_SUCCESS;
}