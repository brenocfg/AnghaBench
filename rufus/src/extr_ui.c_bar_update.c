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
typedef  scalar_t__ uint64_t ;
struct bar_progress_hist {scalar_t__ total_time; scalar_t__* times; size_t pos; scalar_t__* bytes; int /*<<< orphan*/  total_bytes; } ;
struct bar_progress {scalar_t__ recent_start; scalar_t__ recent_bytes; scalar_t__ stalled; struct bar_progress_hist hist; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 size_t SPEED_HISTORY_SIZE ; 
 scalar_t__ SPEED_SAMPLE_MIN ; 
 scalar_t__ STALL_START_TIME ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memset (struct bar_progress_hist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bar_update(struct bar_progress* bp, uint64_t howmuch, uint64_t dltime)
{
	struct bar_progress_hist* hist = &bp->hist;
	uint64_t recent_age = dltime - bp->recent_start;

	// Update the download count.
	bp->recent_bytes += howmuch;

	// For very small time intervals, we return after having updated the
	// "recent" download count. When its age reaches or exceeds minimum
	// sample time, it will be recorded in the history ring.
	if (recent_age < SPEED_SAMPLE_MIN)
		return;

	if (howmuch == 0) {
		// If we're not downloading anything, we might be stalling,
		// i.e. not downloading anything for an extended period of time.
		// Since 0-reads do not enter the history ring, recent_age
		// effectively measures the time since last read.
		if (recent_age >= STALL_START_TIME) {
			// If we're stalling, reset the ring contents because it's
			// stale and because it will make bar_update stop printing
			// the (bogus) current bandwidth.
			bp->stalled = TRUE;
			memset(hist, 0, sizeof(struct bar_progress_hist));
			bp->recent_bytes = 0;
		}
		return;
	}

	// We now have a non-zero amount of to store to the speed ring.

	// If the stall status was acquired, reset it.
	if (bp->stalled) {
		bp->stalled = FALSE;
		// "recent_age" includes the entire stalled period, which
		// could be very long. Don't update the speed ring with that
		// value because the current bandwidth would start too small.
		// Start with an arbitrary (but more reasonable) time value and
		// let it level out.
		recent_age = 1000;
	}

	// Store "recent" bytes and download time to history ring at the position POS.

	// To correctly maintain the totals, first invalidate existing data
	// (least recent in time) at this position. */
	hist->total_time -= hist->times[hist->pos];
	hist->total_bytes -= hist->bytes[hist->pos];

	// Now store the new data and update the totals.
	hist->times[hist->pos] = recent_age;
	hist->bytes[hist->pos] = bp->recent_bytes;
	hist->total_time += recent_age;
	hist->total_bytes += bp->recent_bytes;

	// Start a new "recent" period.
	bp->recent_start = dltime;
	bp->recent_bytes = 0;

	// Advance the current ring position.
	if (++hist->pos == SPEED_HISTORY_SIZE)
		hist->pos = 0;
}