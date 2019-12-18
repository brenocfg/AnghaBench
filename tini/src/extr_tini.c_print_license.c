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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LICENSE ; 
 scalar_t__ LICENSE_len ; 
 scalar_t__ fwrite (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ * const) ; 

void print_license(FILE* const file) {
    if(LICENSE_len > fwrite(LICENSE, sizeof(char), LICENSE_len, file)) {
        // Don't handle this error for now, since parse_args won't care
        // about the return value. We do need to check it to compile with
        // older glibc, though.
        // See: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=25509
        // See: http://sourceware.org/bugzilla/show_bug.cgi?id=11959
    }
}