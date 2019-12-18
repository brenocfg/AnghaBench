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
typedef  int /*<<< orphan*/  fz_document ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fz_drop_page (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fz_load_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ lastPage ; 

__attribute__((used)) static void loadPage(fz_document *doc, int number)
{
	static fz_document *lastPageDoc = NULL;
	static int lastPageNumber = -1;
	if (lastPageNumber != number || lastPageDoc != doc)
	{
		if (lastPage)
			fz_drop_page(ctx, lastPage);
		lastPage = fz_load_page(ctx, doc, number-1);
		lastPageDoc = doc;
		lastPageNumber = number;
	}
}