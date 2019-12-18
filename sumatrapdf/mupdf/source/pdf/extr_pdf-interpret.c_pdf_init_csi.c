#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_lexbuf ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_4__ {int /*<<< orphan*/ * cookie; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * rdb; int /*<<< orphan*/ * doc; } ;
typedef  TYPE_1__ pdf_csi ;
typedef  int /*<<< orphan*/  fz_cookie ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pdf_init_csi(fz_context *ctx, pdf_csi *csi, pdf_document *doc, pdf_obj *rdb, pdf_lexbuf *buf, fz_cookie *cookie)
{
	memset(csi, 0, sizeof *csi);
	csi->doc = doc;
	csi->rdb = rdb;
	csi->buf = buf;
	csi->cookie = cookie;
}