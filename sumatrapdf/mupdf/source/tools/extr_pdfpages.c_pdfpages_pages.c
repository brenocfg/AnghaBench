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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_is_page_range (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  pdf_authenticate_password (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pdf_drop_document (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_needs_password (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_open_document (int /*<<< orphan*/ *,char*) ; 
 int showpages (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
pdfpages_pages(fz_context *ctx, fz_output *out, char *filename, char *password, char *argv[], int argc)
{
	enum { NO_FILE_OPENED, NO_INFO_GATHERED, INFO_SHOWN } state;
	int argidx = 0;
	pdf_document *doc = NULL;
	int ret = 0;

	state = NO_FILE_OPENED;
	while (argidx < argc)
	{
		if (state == NO_FILE_OPENED || !fz_is_page_range(ctx, argv[argidx]))
		{
			if (state == NO_INFO_GATHERED)
			{
				showpages(ctx, doc, out, "1-N");
			}

			pdf_drop_document(ctx, doc);

			filename = argv[argidx];
			fz_write_printf(ctx, out, "%s:\n", filename);
			doc = pdf_open_document(ctx, filename);
			if (pdf_needs_password(ctx, doc))
				if (!pdf_authenticate_password(ctx, doc, password))
					fz_throw(ctx, FZ_ERROR_GENERIC, "cannot authenticate password: %s", filename);

			state = NO_INFO_GATHERED;
		}
		else
		{
			ret |= showpages(ctx, doc, out, argv[argidx]);
			state = INFO_SHOWN;
		}

		argidx++;
	}

	if (state == NO_INFO_GATHERED)
		showpages(ctx, doc, out, "1-N");

	pdf_drop_document(ctx, doc);

	return ret;
}