#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct jpeg_source_mgr {unsigned char* next_input_byte; int bytes_in_buffer; } ;
typedef  TYPE_1__* j_decompress_ptr ;
typedef  int boolean ;
struct TYPE_3__ {struct jpeg_source_mgr* src; } ;

/* Variables and functions */
#define  JPEG_EOI 128 

__attribute__((used)) static boolean fill_input_buffer(j_decompress_ptr cinfo)
{
	static unsigned char eoi[2] = { 0xFF, JPEG_EOI };
	struct jpeg_source_mgr *src = cinfo->src;
	src->next_input_byte = eoi;
	src->bytes_in_buffer = 2;
	return 1;
}