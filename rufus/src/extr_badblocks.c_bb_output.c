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
typedef  long errcode_t ;
typedef  enum error_types { ____Placeholder_error_types } error_types ;
typedef  scalar_t__ blk64_t ;

/* Variables and functions */
 int CORRUPTION_ERROR ; 
 int READ_ERROR ; 
 int WRITE_ERROR ; 
 long bb_badblocks_list_add (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bb_badblocks_list_iterate (scalar_t__,scalar_t__*) ; 
 scalar_t__ bb_badblocks_list_test (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bb_iter ; 
 int /*<<< orphan*/  bb_list ; 
 int /*<<< orphan*/  bb_prefix ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long,char*) ; 
 int /*<<< orphan*/  log_fd ; 
 scalar_t__ next_bad ; 
 int /*<<< orphan*/  num_corruption_errors ; 
 int /*<<< orphan*/  num_read_errors ; 
 int /*<<< orphan*/  num_write_errors ; 
 int /*<<< orphan*/  uprintf (char*,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int bb_output (blk64_t bad, enum error_types error_type)
{
	errcode_t error_code;

	if (bb_badblocks_list_test(bb_list, bad))
		return 0;

	uprintf("%s%lu\n", bb_prefix, (unsigned long)bad);
	fprintf(log_fd, "Block %lu: %s error\n", (unsigned long)bad, (error_type==READ_ERROR)?"read":
		((error_type == WRITE_ERROR)?"write":"corruption"));
	fflush(log_fd);

	error_code = bb_badblocks_list_add(bb_list, bad);
	if (error_code) {
		uprintf("%sError %d adding to in-memory bad block list", bb_prefix, error_code);
		return 0;
	}

	/* kludge:
	   increment the iteration through the bb_list if
	   an element was just added before the current iteration
	   position.  This should not cause next_bad to change. */
	if (bb_iter && bad < next_bad)
		bb_badblocks_list_iterate (bb_iter, &next_bad);

	if (error_type == READ_ERROR) {
	  num_read_errors++;
	} else if (error_type == WRITE_ERROR) {
	  num_write_errors++;
	} else if (error_type == CORRUPTION_ERROR) {
	  num_corruption_errors++;
	}
	return 1;
}