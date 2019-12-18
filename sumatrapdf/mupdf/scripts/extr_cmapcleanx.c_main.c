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
struct cidrange {int lo; int hi; int v; } ;
struct TYPE_11__ {char* cmap_name; int wmode; char* usecmap_name; int codespace_len; int rlen; int xlen; int mlen; TYPE_2__* mranges; TYPE_1__* xranges; TYPE_4__* ranges; TYPE_3__* codespace; } ;
typedef  TYPE_5__ pdf_cmap ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_10__ {int low; int high; int out; } ;
struct TYPE_9__ {int n; int low; int high; } ;
struct TYPE_8__ {int low; int len; int* out; } ;
struct TYPE_7__ {int low; int high; int out; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_STORE_UNLIMITED ; 
 int /*<<< orphan*/  cmpcidrange ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_drop_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cidrange* fz_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fz_new_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_open_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pc (int) ; 
 TYPE_5__* pdf_load_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  qsort (struct cidrange*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char **argv)
{
	fz_context *ctx;
	fz_stream *fi;
	pdf_cmap *cmap;
	int k, m, n, i;
	struct cidrange *r;

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
				printf("<%02x> <%02x>\n", cmap->codespace[k].low, cmap->codespace[k].high);
			else if (cmap->codespace[k].n == 2)
				printf("<%04x> <%04x>\n", cmap->codespace[k].low, cmap->codespace[k].high);
			else if (cmap->codespace[k].n == 3)
				printf("<%06x> <%06x>\n", cmap->codespace[k].low, cmap->codespace[k].high);
			else if (cmap->codespace[k].n == 4)
				printf("<%08x> <%08x>\n", cmap->codespace[k].low, cmap->codespace[k].high);
			else
				printf("<%x> <%x>\n", cmap->codespace[k].low, cmap->codespace[k].high);
		}
		printf("endcodespacerange\n");
	}

	n = cmap->rlen + cmap->xlen;
	r = fz_malloc(ctx, n * sizeof *r);
	i = 0;

	for (k = 0; k < cmap->rlen; k++) {
		r[i].lo = cmap->ranges[k].low;
		r[i].hi = cmap->ranges[k].high;
		r[i].v = cmap->ranges[k].out;
		++i;
	}

	for (k = 0; k < cmap->xlen; k++) {
		r[i].lo = cmap->xranges[k].low;
		r[i].hi = cmap->xranges[k].high;
		r[i].v = cmap->xranges[k].out;
		++i;
	}

	qsort(r, n, sizeof *r, cmpcidrange);

	if (n)
	{
		printf("begincidchar\n");
		for (i = 0; i < n; ++i)
		{
			for (k = r[i].lo, m = r[i].v; k <= r[i].hi; ++k, ++m)
			{
				pc(k);
				printf("%u\n", m);
			}
		}
		printf("endcidchar\n");
	}

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