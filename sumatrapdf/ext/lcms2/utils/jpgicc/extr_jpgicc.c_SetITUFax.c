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
typedef  int /*<<< orphan*/  j_compress_ptr ;

/* Variables and functions */
 scalar_t__ JPEG_APP0 ; 
 int /*<<< orphan*/  jpeg_write_marker (int /*<<< orphan*/ ,scalar_t__,unsigned char*,int) ; 

__attribute__((used)) static
void SetITUFax(j_compress_ptr cinfo)
{
    unsigned char Marker[] = "G3FAX\x00\0x07\xCA\x00\xC8";

    jpeg_write_marker(cinfo, (JPEG_APP0 + 1), Marker, 10);
}