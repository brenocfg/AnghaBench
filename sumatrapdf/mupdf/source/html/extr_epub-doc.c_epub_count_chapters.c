#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {TYPE_2__* spine; } ;
typedef  TYPE_1__ epub_document ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_2__ epub_chapter ;

/* Variables and functions */

__attribute__((used)) static int
epub_count_chapters(fz_context *ctx, fz_document *doc_)
{
	epub_document *doc = (epub_document*)doc_;
	epub_chapter *ch;
	int count = 0;
	for (ch = doc->spine; ch; ch = ch->next)
		++count;
	return count;
}