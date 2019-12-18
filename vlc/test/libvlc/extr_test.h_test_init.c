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
struct sigaction {int /*<<< orphan*/  sa_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  alarm (unsigned int) ; 
 int atoi (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  on_timeout ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_default_sample ; 

__attribute__((used)) static inline void test_init (void)
{
    (void)test_default_sample; /* This one may not be used */

    /* Make sure "make check" does not get stuck */
    /* Timeout of 10secs by default */
    unsigned alarm_timeout = 10;
    /* Valid timeout value are < 0, for infinite, and > 0, for the number of
     * seconds */
    char *alarm_timeout_str = getenv("VLC_TEST_TIMEOUT");
    if (alarm_timeout_str)
    {
        int val = atoi(alarm_timeout_str);
        if (val <= 0)
            alarm_timeout = 0; /* infinite */
        else
            alarm_timeout = val;
    }
    if (alarm_timeout != 0)
    {
        struct sigaction sig = {
            .sa_handler = on_timeout,
        };
        sigaction(SIGALRM, &sig, NULL);
        alarm (alarm_timeout);
    }

    setenv( "VLC_PLUGIN_PATH", "../modules", 1 );
}