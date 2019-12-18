#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float e; float f; int /*<<< orphan*/  d; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float floorf (float) ; 
 float fz_matrix_expansion (TYPE_1__) ; 

float
fz_subpixel_adjust(fz_context *ctx, fz_matrix *ctm, fz_matrix *subpix_ctm, unsigned char *qe, unsigned char *qf)
{
	float size = fz_matrix_expansion(*ctm);
	int q;
	float pix_e, pix_f, r;

	/* Quantise the subpixel positions. */
	/* We never need more than 4 subpixel positions for glyphs - arguably
	 * even that is too much. */
	if (size >= 48)
		q = 0, r = 0.5f;
	else if (size >= 24)
		q = 128, r = 0.25f;
	else
		q = 192, r = 0.125f;

	/* Split translation into pixel and subpixel parts */
	subpix_ctm->a = ctm->a;
	subpix_ctm->b = ctm->b;
	subpix_ctm->c = ctm->c;
	subpix_ctm->d = ctm->d;
	subpix_ctm->e = ctm->e + r;
	pix_e = floorf(subpix_ctm->e);
	subpix_ctm->e -= pix_e;
	subpix_ctm->f = ctm->f + r;
	pix_f = floorf(subpix_ctm->f);
	subpix_ctm->f -= pix_f;

	/* Quantise the subpixel part */
	*qe = (int)(subpix_ctm->e * 256) & q;
	subpix_ctm->e = *qe / 256.0f;
	*qf = (int)(subpix_ctm->f * 256) & q;
	subpix_ctm->f = *qf / 256.0f;

	/* Reassemble the complete translation */
	ctm->e = subpix_ctm->e + pix_e;
	ctm->f = subpix_ctm->f + pix_f;

	return size;
}