#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ data_buffer_t ;

/* Variables and functions */
 int data_buffer_compare (TYPE_1__ const,TYPE_1__ const) ; 
 int /*<<< orphan*/  data_buffer_free (TYPE_1__ const) ; 
 TYPE_1__ data_buffer_read (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int diff_results(char const* actual_file, char const* expected_file) {
    data_buffer_t const actual = data_buffer_read(actual_file);
    data_buffer_t const expected = data_buffer_read(expected_file);
    int ret = 1;

    if (actual.data == NULL) {
        fprintf(stderr, "failed to open results '%s' for diff\n", actual_file);
        goto out;
    }
    if (expected.data == NULL) {
        fprintf(
            stderr,
            "failed to open previous results '%s' for diff\n",
            expected_file);
        goto out;
    }

    ret = data_buffer_compare(actual, expected);
    if (ret != 0) {
        fprintf(
            stderr,
            "actual results '%s' does not match expected results '%s'\n",
            actual_file,
            expected_file);
    } else {
        fprintf(stderr, "actual results match expected results\n");
    }
out:
    data_buffer_free(actual);
    data_buffer_free(expected);
    return ret;
}