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
typedef  int /*<<< orphan*/  xps_document ;
struct stop {float offset; int /*<<< orphan*/  a; int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct TYPE_3__ {void*** function; } ;
typedef  TYPE_1__ fz_shade ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* lerp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void
xps_sample_gradient_stops(fz_context *ctx, xps_document *doc, fz_shade *shade, struct stop *stops, int count)
{
	float offset, d;
	int i, k;

	k = 0;
	for (i = 0; i < 256; i++)
	{
		offset = i / 255.0f;
		while (k + 1 < count && offset > stops[k+1].offset)
			k++;

		d = (offset - stops[k].offset) / (stops[k+1].offset - stops[k].offset);

		shade->function[i][0] = lerp(stops[k].r, stops[k+1].r, d);
		shade->function[i][1] = lerp(stops[k].g, stops[k+1].g, d);
		shade->function[i][2] = lerp(stops[k].b, stops[k+1].b, d);
		shade->function[i][3] = lerp(stops[k].a, stops[k+1].a, d);
	}
}