#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_rect ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ fz_link ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_new_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
xps_add_link(fz_context *ctx, xps_document *doc, fz_rect area, char *base_uri, char *target_uri, fz_link **head)
{
	fz_link *link = fz_new_link(ctx, area, doc, target_uri);
	link->next = *head;
	*head = link;
}