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
struct TYPE_3__ {int /*<<< orphan*/  intent; } ;
typedef  TYPE_1__ pdf_ocg_descriptor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* pdf_to_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
ocg_intents_include(fz_context *ctx, pdf_ocg_descriptor *desc, const char *name)
{
	int i, len;

	if (strcmp(name, "All") == 0)
		return 1;

	/* In the absence of a specified intent, it's 'View' */
	if (!desc->intent)
		return (strcmp(name, "View") == 0);

	if (pdf_is_name(ctx, desc->intent))
	{
		const char *intent = pdf_to_name(ctx, desc->intent);
		if (strcmp(intent, "All") == 0)
			return 1;
		return (strcmp(intent, name) == 0);
	}
	if (!pdf_is_array(ctx, desc->intent))
		return 0;

	len = pdf_array_len(ctx, desc->intent);
	for (i=0; i < len; i++)
	{
		const char *intent = pdf_to_name(ctx, pdf_array_get(ctx, desc->intent, i));
		if (strcmp(intent, "All") == 0)
			return 1;
		if (strcmp(intent, name) == 0)
			return 1;
	}
	return 0;
}