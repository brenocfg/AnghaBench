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
typedef  int /*<<< orphan*/  UTIL_time_t ;

/* Variables and functions */
 double UTIL_getSpanTimeMicro (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTIL_getTime () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_startTime ; 
 scalar_t__ g_streamedSize ; 
 int /*<<< orphan*/  g_useProgressBar ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void displayProgress(unsigned cLevel, unsigned last)
{
    UTIL_time_t currTime = UTIL_getTime();
    if (!g_useProgressBar) return;
    {   double const timeElapsed = (double)(UTIL_getSpanTimeMicro(g_startTime, currTime) / 1000.0);
        double const sizeMB = (double)g_streamedSize / (1 << 20);
        double const avgCompRate = sizeMB * 1000 / timeElapsed;
        fprintf(stderr, "\r| Comp. Level: %2u | Time Elapsed: %7.2f s | Data Size: %7.1f MB | Avg Comp. Rate: %6.2f MB/s |", cLevel, timeElapsed/1000.0, sizeMB, avgCompRate);
        if (last) {
            fprintf(stderr, "\n");
        } else {
            fflush(stderr);
    }   }
}