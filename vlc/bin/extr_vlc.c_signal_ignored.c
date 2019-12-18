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
struct sigaction {int sa_flags; scalar_t__ sa_handler; scalar_t__ sa_sigaction; } ;

/* Variables and functions */
 int SA_SIGINFO ; 
 void* SIG_IGN ; 
 scalar_t__ sigaction (int,int /*<<< orphan*/ *,struct sigaction*) ; 

__attribute__((used)) static bool signal_ignored (int signum)
{
    struct sigaction sa;

    if (sigaction (signum, NULL, &sa))
        return false;
    return ((sa.sa_flags & SA_SIGINFO)
            ? (void *)sa.sa_sigaction : (void *)sa.sa_handler) == SIG_IGN;
}