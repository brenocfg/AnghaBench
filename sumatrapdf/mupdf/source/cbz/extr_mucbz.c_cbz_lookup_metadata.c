#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {int /*<<< orphan*/  arch; } ;
typedef  TYPE_1__ cbz_document ;

/* Variables and functions */
 int /*<<< orphan*/  fz_archive_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int
cbz_lookup_metadata(fz_context *ctx, fz_document *doc_, const char *key, char *buf, int size)
{
	cbz_document *doc = (cbz_document*)doc_;
	if (!strcmp(key, "format"))
		return (int) fz_strlcpy(buf, fz_archive_format(ctx, doc->arch), size);
	return -1;
}