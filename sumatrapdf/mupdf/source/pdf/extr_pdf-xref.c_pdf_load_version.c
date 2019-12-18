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
struct TYPE_3__ {int version; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 float fz_atof (char*) ; 
 int /*<<< orphan*/  fz_read_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fz_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
pdf_load_version(fz_context *ctx, pdf_document *doc)
{
	char buf[20];

	fz_seek(ctx, doc->file, 0, SEEK_SET);
	fz_read_line(ctx, doc->file, buf, sizeof buf);
	if (strlen(buf) < 5 || memcmp(buf, "%PDF-", 5) != 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot recognize version marker");

	doc->version = 10 * (fz_atof(buf+5) + 0.05f);
	if (doc->version < 10 || doc->version > 17)
		if (doc->version != 20)
			fz_warn(ctx, "unknown PDF version: %d.%d", doc->version / 10, doc->version % 10);
}