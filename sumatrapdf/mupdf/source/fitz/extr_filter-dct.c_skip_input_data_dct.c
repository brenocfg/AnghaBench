#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct jpeg_source_mgr {size_t bytes_in_buffer; long next_input_byte; int /*<<< orphan*/  (* fill_input_buffer ) (TYPE_1__*) ;} ;
typedef  TYPE_1__* j_decompress_ptr ;
struct TYPE_4__ {struct jpeg_source_mgr* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void skip_input_data_dct(j_decompress_ptr cinfo, long num_bytes)
{
	struct jpeg_source_mgr *src = cinfo->src;
	if (num_bytes > 0)
	{
		while ((size_t)num_bytes > src->bytes_in_buffer)
		{
			num_bytes -= (long)src->bytes_in_buffer;
			(void) src->fill_input_buffer(cinfo);
		}
		src->next_input_byte += num_bytes;
		src->bytes_in_buffer -= num_bytes;
	}
}