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
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 char* xps_parse_float_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,float*) ; 

char *
xps_parse_point(fz_context *ctx, xps_document *doc, char *s_in, float *x, float *y)
{
	char *s_out = s_in;
	float xy[2];

	s_out = xps_parse_float_array(ctx, doc, s_out, 2, &xy[0]);
	*x = xy[0];
	*y = xy[1];
	return s_out;
}