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
 int /*<<< orphan*/  prt_dsc_noarg (char*) ; 
 int /*<<< orphan*/  prt_file_error ; 
 int /*<<< orphan*/  prt_flush_buffer () ; 
 int /*<<< orphan*/  prt_write_string (char*) ; 

int
mch_print_end_page()
{
    prt_flush_buffer();

    prt_write_string("re sp\n");

    prt_dsc_noarg("PageTrailer");

    return !prt_file_error;
}