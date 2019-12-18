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
typedef  TYPE_1__* jpeg_saved_marker_ptr ;
struct TYPE_3__ {scalar_t__ marker; int data_length; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ JPEG_APP0 ; 
 int read_value (unsigned char const*,int,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int extract_app13_resolution(jpeg_saved_marker_ptr marker, int *xres, int *yres)
{
	const unsigned char *data, *data_end;

	if (!marker || marker->marker != JPEG_APP0 + 13 || marker->data_length < 42 ||
		strcmp((const char *)marker->data, "Photoshop 3.0") != 0)
	{
		return 0;
	}

	data = (const unsigned char *)marker->data;
	data_end = data + marker->data_length;
	for (data += 14; data + 12 < data_end; ) {
		int data_size = -1;
		int tag = read_value(data + 4, 2, 1);
		int value_off = 11 + read_value(data + 6, 2, 1);
		if (value_off % 2 == 1)
			value_off++;
		if (read_value(data, 4, 1) == 0x3842494D /* 8BIM */ && value_off <= data_end - data)
			data_size = read_value(data + value_off - 4, 4, 1);
		if (data_size < 0 || data_size > data_end - data - value_off)
			return 0;
		if (tag == 0x3ED && data_size == 16)
		{
			*xres = read_value(data + value_off, 2, 1);
			*yres = read_value(data + value_off + 8, 2, 1);
			return 1;
		}
		if (data_size % 2 == 1)
			data_size++;
		data += value_off + data_size;
	}

	return 0;
}