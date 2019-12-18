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
 scalar_t__ pdf_to_str_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_to_str_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_binary_string(fz_context *ctx, pdf_obj *obj)
{
	unsigned char *s = (unsigned char *)pdf_to_str_buf(ctx, obj);
	int i, n = pdf_to_str_len(ctx, obj);
	for (i = 0; i < n; ++i)
	{
		if (s[i] > 126) return 1;
		if (s[i] < 32 && (s[i] != '\t' && s[i] != '\n' && s[i] != '\r')) return 1;
	}
	return 0;
}