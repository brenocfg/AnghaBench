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
struct TYPE_3__ {int startxref; int /*<<< orphan*/  file; scalar_t__ file_size; } ;
typedef  TYPE_1__ pdf_document ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int INT64_MAX ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ fz_maxi64 (int /*<<< orphan*/ ,scalar_t__) ; 
 size_t fz_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_tell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ iswhite (unsigned char) ; 
 scalar_t__ memcmp (unsigned char*,char*,int) ; 

__attribute__((used)) static void
pdf_read_start_xref(fz_context *ctx, pdf_document *doc)
{
	unsigned char buf[1024];
	size_t i, n;
	int64_t t;

	fz_seek(ctx, doc->file, 0, SEEK_END);

	doc->file_size = fz_tell(ctx, doc->file);

	t = fz_maxi64(0, doc->file_size - (int64_t)sizeof buf);
	fz_seek(ctx, doc->file, t, SEEK_SET);

	n = fz_read(ctx, doc->file, buf, sizeof buf);
	if (n < 9)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find startxref");

	i = n - 9;
	do
	{
		if (memcmp(buf + i, "startxref", 9) == 0)
		{
			i += 9;
			while (i < n && iswhite(buf[i]))
				i ++;
			doc->startxref = 0;
			while (i < n && isdigit(buf[i]))
			{
				if (doc->startxref >= INT64_MAX/10)
					fz_throw(ctx, FZ_ERROR_GENERIC, "startxref too large");
				doc->startxref = doc->startxref * 10 + (buf[i++] - '0');
			}
			if (doc->startxref != 0)
				return;
			break;
		}
	} while (i-- > 0);

	fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find startxref");
}