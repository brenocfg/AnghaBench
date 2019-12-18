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
struct TYPE_3__ {int do_compress; int do_compress_images; int do_compress_fonts; } ;

/* Variables and functions */
 TYPE_1__ pdf_default_write_options ; 
 TYPE_1__ save_opts ; 

__attribute__((used)) static void init_save_pdf_options(void)
{
	save_opts = pdf_default_write_options;
	save_opts.do_compress = 1;
	save_opts.do_compress_images = 1;
	save_opts.do_compress_fonts = 1;
}