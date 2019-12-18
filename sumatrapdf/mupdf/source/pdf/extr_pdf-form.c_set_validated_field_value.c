#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_6__ {int dirty; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ pdf_field_dirties_document (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_field_event_validate (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  update_field_value (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int set_validated_field_value(fz_context *ctx, pdf_document *doc, pdf_obj *field, const char *text, int ignore_trigger_events)
{
	if (!ignore_trigger_events)
	{
		if (!pdf_field_event_validate(ctx, doc, field, text))
			return 0;
	}

	if (pdf_field_dirties_document(ctx, doc, field))
		doc->dirty = 1;
	update_field_value(ctx, doc, field, text);

	return 1;
}