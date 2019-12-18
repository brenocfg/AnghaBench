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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_thread_id () ; 
 int /*<<< orphan*/  vlc_trace (char const*,char const*,unsigned int) ; 

__attribute__((used)) static void
vlc_thread_fatal (const char *action, int error,
                  const char *function, const char *file, unsigned line)
{
    int canc = vlc_savecancel ();
    fprintf (stderr, "LibVLC fatal error %s (%d) in thread %lu ",
             action, error, vlc_thread_id ());
    vlc_trace (function, file, line);
    perror ("Thread error");
    fflush (stderr);

    vlc_restorecancel (canc);
    abort ();
}