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
typedef  int /*<<< orphan*/  fz_stream ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  fz_drop_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t fz_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/ * pdf_open_raw_stream_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pdf_open_stream_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ showbinary ; 
 scalar_t__ showcolumn ; 
 scalar_t__ showdecode ; 
 int /*<<< orphan*/  showsafe (unsigned char*,size_t) ; 

__attribute__((used)) static void showstream(int num)
{
	fz_stream *stm;
	unsigned char buf[2048];
	size_t n;

	showcolumn = 0;

	if (showdecode)
		stm = pdf_open_stream_number(ctx, doc, num);
	else
		stm = pdf_open_raw_stream_number(ctx, doc, num);

	while (1)
	{
		n = fz_read(ctx, stm, buf, sizeof buf);
		if (n == 0)
			break;
		if (showbinary)
			fz_write_data(ctx, out, buf, n);
		else
			showsafe(buf, n);
	}

	fz_drop_stream(ctx, stm);
}