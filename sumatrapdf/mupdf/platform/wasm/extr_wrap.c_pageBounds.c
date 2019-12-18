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
typedef  int /*<<< orphan*/  fz_irect ;
typedef  int /*<<< orphan*/  fz_document ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fz_bound_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_round_rect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_scale (float,float) ; 
 int /*<<< orphan*/  fz_transform_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lastPage ; 
 int /*<<< orphan*/  loadPage (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static fz_irect pageBounds(fz_document *doc, int number, float dpi)
{
	loadPage(doc, number);
	return fz_round_rect(fz_transform_rect(fz_bound_page(ctx, lastPage), fz_scale(dpi/72, dpi/72)));
}