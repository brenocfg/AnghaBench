#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pdf_token ;
struct TYPE_6__ {int /*<<< orphan*/  scratch; } ;
typedef  TYPE_1__ pdf_lexbuf ;
struct TYPE_7__ {int /*<<< orphan*/  cmap_name; } ;
typedef  TYPE_2__ pdf_cmap ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ PDF_TOK_NAME ; 
 int /*<<< orphan*/  fz_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pdf_lex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
pdf_parse_cmap_name(fz_context *ctx, pdf_cmap *cmap, fz_stream *file, pdf_lexbuf *buf)
{
	pdf_token tok;

	tok = pdf_lex(ctx, file, buf);

	if (tok == PDF_TOK_NAME)
		fz_strlcpy(cmap->cmap_name, buf->scratch, sizeof(cmap->cmap_name));
	else
		fz_warn(ctx, "expected name after CMapName in cmap");
}