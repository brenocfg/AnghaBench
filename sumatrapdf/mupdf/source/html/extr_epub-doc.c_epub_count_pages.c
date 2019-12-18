#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {TYPE_2__* spine; } ;
typedef  TYPE_1__ epub_document ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ epub_chapter ;

/* Variables and functions */
 int count_chapter_pages (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int
epub_count_pages(fz_context *ctx, fz_document *doc_, int chapter)
{
	epub_document *doc = (epub_document*)doc_;
	epub_chapter *ch;
	int i;
	for (i = 0, ch = doc->spine; ch; ++i, ch = ch->next)
	{
		if (i == chapter)
		{
			return count_chapter_pages(ctx, doc, ch);
		}
	}
	return 0;
}