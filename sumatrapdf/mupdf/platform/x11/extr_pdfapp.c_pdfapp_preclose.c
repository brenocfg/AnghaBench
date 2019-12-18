#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  doc; } ;
typedef  TYPE_1__ pdfapp_t ;
typedef  int /*<<< orphan*/  pdf_document ;

/* Variables and functions */
#define  CANCEL 130 
#define  DISCARD 129 
#define  SAVE 128 
 scalar_t__ pdf_has_unsaved_changes (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_specifics (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pdfapp_save (TYPE_1__*) ; 
 int winsavequery (TYPE_1__*) ; 

int pdfapp_preclose(pdfapp_t *app)
{
	pdf_document *idoc = pdf_specifics(app->ctx, app->doc);

	if (idoc && pdf_has_unsaved_changes(app->ctx, idoc))
	{
		switch (winsavequery(app))
		{
		case DISCARD:
			return 1;

		case CANCEL:
			return 0;

		case SAVE:
			return pdfapp_save(app);
		}
	}

	return 1;
}