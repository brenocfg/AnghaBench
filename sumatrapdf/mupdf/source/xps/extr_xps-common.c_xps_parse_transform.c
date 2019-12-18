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
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xps_parse_matrix_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_parse_render_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

fz_matrix
xps_parse_transform(fz_context *ctx, xps_document *doc, char *att, fz_xml *tag, fz_matrix ctm)
{
	if (att)
		return fz_concat(xps_parse_render_transform(ctx, doc, att), ctm);
	if (tag)
		return fz_concat(xps_parse_matrix_transform(ctx, doc, tag), ctm);
	return ctm;
}