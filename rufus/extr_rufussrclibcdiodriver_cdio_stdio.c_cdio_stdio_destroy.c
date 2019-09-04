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
typedef  int /*<<< orphan*/  CdioDataSource_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_stream_destroy (int /*<<< orphan*/ *) ; 

void
cdio_stdio_destroy(CdioDataSource_t *p_obj)
{
  cdio_stream_destroy(p_obj);
}