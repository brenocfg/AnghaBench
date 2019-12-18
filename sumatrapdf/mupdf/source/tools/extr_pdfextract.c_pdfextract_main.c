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

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  FZ_STORE_UNLIMITED ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 int doicc ; 
 int /*<<< orphan*/  dorgb ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  extractobject (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_disable_icc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_enable_icc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_flush_warnings (int /*<<< orphan*/ ) ; 
 int fz_getopt (int,char**,char*) ; 
 int /*<<< orphan*/  fz_new_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* fz_optarg ; 
 int fz_optind ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pdf_authenticate_password (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int pdf_count_objects (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_drop_document (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_needs_password (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_open_document (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 

int pdfextract_main(int argc, char **argv)
{
	char *infile;
	char *password = "";
	int c, o;

	while ((c = fz_getopt(argc, argv, "p:rN")) != -1)
	{
		switch (c)
		{
		case 'p': password = fz_optarg; break;
		case 'r': dorgb++; break;
		case 'N': doicc^=1; break;
		default: usage(); break;
		}
	}

	if (fz_optind == argc)
		usage();

	infile = argv[fz_optind++];

	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if (!ctx)
	{
		fprintf(stderr, "cannot initialise context\n");
		exit(1);
	}

	if (doicc)
		fz_enable_icc(ctx);
	else
		fz_disable_icc(ctx);

	doc = pdf_open_document(ctx, infile);
	if (pdf_needs_password(ctx, doc))
		if (!pdf_authenticate_password(ctx, doc, password))
			fz_throw(ctx, FZ_ERROR_GENERIC, "cannot authenticate password: %s", infile);

	if (fz_optind == argc)
	{
		int len = pdf_count_objects(ctx, doc);
		for (o = 1; o < len; o++)
			extractobject(o);
	}
	else
	{
		while (fz_optind < argc)
		{
			extractobject(atoi(argv[fz_optind]));
			fz_optind++;
		}
	}

	pdf_drop_document(ctx, doc);
	fz_flush_warnings(ctx);
	fz_drop_context(ctx);
	return 0;
}