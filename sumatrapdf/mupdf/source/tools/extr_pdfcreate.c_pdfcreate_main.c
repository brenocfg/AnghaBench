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
typedef  int /*<<< orphan*/  pdf_write_options ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_STORE_UNLIMITED ; 
 int /*<<< orphan*/  create_page (char*) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_drop_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_flush_warnings (int /*<<< orphan*/ ) ; 
 int fz_getopt (int,char**,char*) ; 
 int /*<<< orphan*/  fz_new_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* fz_optarg ; 
 int fz_optind ; 
 int /*<<< orphan*/  pdf_create_document (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_default_write_options ; 
 int /*<<< orphan*/  pdf_drop_document (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_parse_write_options (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pdf_save_document (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 

int pdfcreate_main(int argc, char **argv)
{
	pdf_write_options opts = pdf_default_write_options;
	char *output = "out.pdf";
	char *flags = "compress";
	int i, c;

	while ((c = fz_getopt(argc, argv, "o:O:")) != -1)
	{
		switch (c)
		{
		case 'o': output = fz_optarg; break;
		case 'O': flags = fz_optarg; break;
		default: usage(); break;
		}
	}

	if (fz_optind == argc)
		usage();

	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if (!ctx)
	{
		fprintf(stderr, "cannot initialise context\n");
		exit(1);
	}

	pdf_parse_write_options(ctx, &opts, flags);

	doc = pdf_create_document(ctx);

	for (i = fz_optind; i < argc; ++i)
		create_page(argv[i]);

	pdf_save_document(ctx, doc, output, &opts);

	pdf_drop_document(ctx, doc);

	fz_flush_warnings(ctx);
	fz_drop_context(ctx);
	return 0;
}