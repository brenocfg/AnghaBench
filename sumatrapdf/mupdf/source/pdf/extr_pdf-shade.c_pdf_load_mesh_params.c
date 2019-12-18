#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_5__ {int x1; int y1; int* c1; int vprow; int bpflag; int bpcoord; int bpcomp; void** c0; void* y0; void* x0; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_7__ {int type; TYPE_2__ u; } ;
typedef  TYPE_3__ fz_shade ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  BitsPerComponent ; 
 int /*<<< orphan*/  BitsPerCoordinate ; 
 int /*<<< orphan*/  BitsPerFlag ; 
 int /*<<< orphan*/  Decode ; 
 int FZ_MAX_COLORS ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VerticesPerRow ; 
 int fz_mini (int,int) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int) ; 
 void* pdf_array_get_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* pdf_dict_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_load_mesh_params(fz_context *ctx, pdf_document *doc, fz_shade *shade, pdf_obj *dict)
{
	pdf_obj *obj;
	int i, n;

	shade->u.m.x0 = shade->u.m.y0 = 0;
	shade->u.m.x1 = shade->u.m.y1 = 1;
	for (i = 0; i < FZ_MAX_COLORS; i++)
	{
		shade->u.m.c0[i] = 0;
		shade->u.m.c1[i] = 1;
	}

	shade->u.m.vprow = pdf_dict_get_int(ctx, dict, PDF_NAME(VerticesPerRow));
	shade->u.m.bpflag = pdf_dict_get_int(ctx, dict, PDF_NAME(BitsPerFlag));
	shade->u.m.bpcoord = pdf_dict_get_int(ctx, dict, PDF_NAME(BitsPerCoordinate));
	shade->u.m.bpcomp = pdf_dict_get_int(ctx, dict, PDF_NAME(BitsPerComponent));

	obj = pdf_dict_get(ctx, dict, PDF_NAME(Decode));
	if (pdf_array_len(ctx, obj) >= 6)
	{
		n = fz_mini(FZ_MAX_COLORS, (pdf_array_len(ctx, obj) - 4) / 2);
		shade->u.m.x0 = pdf_array_get_real(ctx, obj, 0);
		shade->u.m.x1 = pdf_array_get_real(ctx, obj, 1);
		shade->u.m.y0 = pdf_array_get_real(ctx, obj, 2);
		shade->u.m.y1 = pdf_array_get_real(ctx, obj, 3);
		for (i = 0; i < n; i++)
		{
			shade->u.m.c0[i] = pdf_array_get_real(ctx, obj, 4 + i * 2);
			shade->u.m.c1[i] = pdf_array_get_real(ctx, obj, 5 + i * 2);
		}
	}

	if (shade->u.m.vprow < 2 && shade->type == 5)
	{
		fz_warn(ctx, "Too few vertices per row (%d)", shade->u.m.vprow);
		shade->u.m.vprow = 2;
	}

	if (shade->u.m.bpflag != 2 && shade->u.m.bpflag != 4 && shade->u.m.bpflag != 8 &&
		shade->type != 5)
	{
		fz_warn(ctx, "Invalid number of bits per flag (%d)", shade->u.m.bpflag);
		shade->u.m.bpflag = 8;
	}

	if (shade->u.m.bpcoord != 1 && shade->u.m.bpcoord != 2 && shade->u.m.bpcoord != 4 &&
		shade->u.m.bpcoord != 8 && shade->u.m.bpcoord != 12 && shade->u.m.bpcoord != 16 &&
		shade->u.m.bpcoord != 24 && shade->u.m.bpcoord != 32)
	{
		fz_warn(ctx, "Invalid number of bits per coordinate (%d)", shade->u.m.bpcoord);
		shade->u.m.bpcoord = 8;
	}

	if (shade->u.m.bpcomp != 1 && shade->u.m.bpcomp != 2 && shade->u.m.bpcomp != 4 &&
		shade->u.m.bpcomp != 8 && shade->u.m.bpcomp != 12 && shade->u.m.bpcomp != 16)
	{
		fz_warn(ctx, "Invalid number of bits per component (%d)", shade->u.m.bpcomp);
		shade->u.m.bpcomp = 8;
	}
}