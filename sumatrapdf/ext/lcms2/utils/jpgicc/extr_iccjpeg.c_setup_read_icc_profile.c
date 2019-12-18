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
typedef  int /*<<< orphan*/  j_decompress_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  ICC_MARKER ; 
 int /*<<< orphan*/  jpeg_save_markers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
setup_read_icc_profile (j_decompress_ptr cinfo)
{
  /* Tell the library to keep any APP2 data it may find */
  jpeg_save_markers(cinfo, ICC_MARKER, 0xFFFF);
}