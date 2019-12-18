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

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*) ; 
 int SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int UTIL_isRegularFile (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ g_artefact ; 
 int /*<<< orphan*/  remove (scalar_t__) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void INThandler(int sig)
{
    assert(sig==SIGINT); (void)sig;
#if !defined(_MSC_VER)
    signal(sig, SIG_IGN);  /* this invocation generates a buggy warning in Visual Studio */
#endif
    if (g_artefact) {
        assert(UTIL_isRegularFile(g_artefact));
        remove(g_artefact);
    }
    DISPLAY("\n");
    exit(2);
}