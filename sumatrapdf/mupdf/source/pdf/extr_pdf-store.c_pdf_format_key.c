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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_strlcpy (char*,char*,int) ; 
 scalar_t__ pdf_is_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* pdf_sprint_obj (int /*<<< orphan*/ *,char*,int,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pdf_format_key(fz_context *ctx, char *s, int n, void *key_)
{
	pdf_obj *key = (pdf_obj *)key_;
	if (pdf_is_indirect(ctx, key))
		fz_snprintf(s, n, "(%d 0 R)", pdf_to_num(ctx, key));
	else
	{
		int t;
		char *p = pdf_sprint_obj(ctx, s, n, &t, key, 1, 0);
		if (p != s) {
			fz_strlcpy(s, p, n);
			fz_free(ctx, p);
		}
	}
}