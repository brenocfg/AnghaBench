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
typedef  int /*<<< orphan*/  pdfapp_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdfapp_error (int /*<<< orphan*/ *,char*) ; 

void wincopyfile(pdfapp_t *app, char *source, char *target)
{
	FILE *in, *out;
	char buf[32 << 10];
	size_t n;

	in = fopen(source, "rb");
	if (!in)
	{
		pdfapp_error(app, "cannot open source file for copying");
		return;
	}
	out = fopen(target, "wb");
	if (!out)
	{
		pdfapp_error(app, "cannot open target file for copying");
		fclose(in);
		return;
	}

	for (;;)
	{
		n = fread(buf, 1, sizeof buf, in);
		fwrite(buf, 1, n, out);
		if (n < sizeof buf)
		{
			if (ferror(in))
				pdfapp_error(app, "cannot read data from source file");
			break;
		}
	}

	fclose(out);
	fclose(in);
}