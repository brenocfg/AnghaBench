#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* cmap_name; int wmode; char* usecmap_name; int codespace_len; int rlen; int xlen; int mlen; TYPE_3__* mranges; TYPE_2__* xranges; TYPE_1__* ranges; TYPE_4__* codespace; } ;
typedef  TYPE_5__ pdf_cmap ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_10__ {int n; int low; int high; } ;
struct TYPE_9__ {scalar_t__ low; int len; int* out; } ;
struct TYPE_8__ {scalar_t__ high; scalar_t__ low; int out; } ;
struct TYPE_7__ {scalar_t__ high; scalar_t__ low; int out; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_STORE_UNLIMITED ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_drop_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_new_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_open_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pc (scalar_t__) ; 
 TYPE_5__* pdf_load_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char **argv)
{
	fz_context *ctx;
	fz_stream *fi;
	pdf_cmap *cmap;
	int k, m;
	int ns, nr;

	if (argc != 2)
	{
		fprintf(stderr, "usage: cmapclean input.cmap\n");
		return 1;
	}

	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if (!ctx)
	{
		fprintf(stderr, "cannot initialise context\n");
		return 1;
	}

	fi = fz_open_file(ctx, argv[1]);
	cmap = pdf_load_cmap(ctx, fi);
	fz_drop_stream(ctx, fi);

	printf("begincmap\n");
	printf("/CMapName /%s def\n", cmap->cmap_name);
	printf("/WMode %d def\n", cmap->wmode);
	if (cmap->usecmap_name[0])
		printf("/%s usecmap\n", cmap->usecmap_name);

	if (cmap->codespace_len)
	{
		printf("begincodespacerange\n");
		for (k = 0; k < cmap->codespace_len; k++)
		{
			if (cmap->codespace[k].n == 1)
				printf("<%02x><%02x>\n", cmap->codespace[k].low, cmap->codespace[k].high);
			else if (cmap->codespace[k].n == 2)
				printf("<%04x><%04x>\n", cmap->codespace[k].low, cmap->codespace[k].high);
			else if (cmap->codespace[k].n == 3)
				printf("<%06x><%06x>\n", cmap->codespace[k].low, cmap->codespace[k].high);
			else if (cmap->codespace[k].n == 4)
				printf("<%08x><%08x>\n", cmap->codespace[k].low, cmap->codespace[k].high);
			else
				printf("<%x><%x>\n", cmap->codespace[k].low, cmap->codespace[k].high);
		}
		printf("endcodespacerange\n");
	}

	/* 16-bit ranges */

	ns = nr = 0;
	for (k = 0; k < cmap->rlen; k++)
		if (cmap->ranges[k].high - cmap->ranges[k].low > 0)
			++nr;
		else
			++ns;

	if (ns)
	{
		printf("begincidchar\n");
		for (k = 0; k < cmap->rlen; k++) {
			if (cmap->ranges[k].high - cmap->ranges[k].low == 0) {
				pc(cmap->ranges[k].low);
				printf(" %u\n", cmap->ranges[k].out);
			}
		}
		printf("endcidchar\n");
	}

	if (nr)
	{
		printf("begincidrange\n");
		for (k = 0; k < cmap->rlen; k++) {
			if (cmap->ranges[k].high - cmap->ranges[k].low > 0) {
				pc(cmap->ranges[k].low);
				putchar(' ');
				pc(cmap->ranges[k].high);
				printf(" %u\n", cmap->ranges[k].out);
			}
		}
		printf("endcidrange\n");
	}

	/* 32-bit ranges */

	ns = nr = 0;
	for (k = 0; k < cmap->xlen; k++)
		if (cmap->xranges[k].high - cmap->xranges[k].low > 0)
			++nr;
		else
			++ns;

	if (ns)
	{
		printf("begincidchar\n");
		for (k = 0; k < cmap->xlen; k++) {
			if (cmap->xranges[k].high - cmap->xranges[k].low == 0) {
				pc(cmap->xranges[k].low);
				printf("%u\n", cmap->xranges[k].out);
			}
		}
		printf("endcidchar\n");
	}

	if (nr)
	{
		printf("begincidrange\n");
		for (k = 0; k < cmap->xlen; k++) {
			if (cmap->xranges[k].high - cmap->xranges[k].low > 0) {
				pc(cmap->xranges[k].low);
				pc(cmap->xranges[k].high);
				printf("%u\n", cmap->xranges[k].out);
			}
		}
		printf("endcidrange\n");
	}

	/* 1-to-many */

#if 0
	if (cmap->mlen > 0)
	{
		printf("beginbfchar\n");
		for (k = 0; k < cmap->mlen; k++)
		{
			pc(cmap->mranges[k].low);
			printf("<");
			for (m = 0; m < cmap->mranges[k].len; ++m)
				printf("%04x", cmap->mranges[k].out[m]);
			printf(">\n");
		}
		printf("endbfchar\n");
	}
#endif

	printf("endcmap\n");

	fz_drop_context(ctx);
	return 0;
}