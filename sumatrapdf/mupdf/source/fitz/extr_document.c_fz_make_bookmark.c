#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int chapter; scalar_t__ page; } ;
typedef  TYPE_1__ fz_location ;
struct TYPE_8__ {scalar_t__ (* make_bookmark ) (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__) ;} ;
typedef  TYPE_2__ fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  scalar_t__ fz_bookmark ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__) ; 

fz_bookmark fz_make_bookmark(fz_context *ctx, fz_document *doc, fz_location loc)
{
	if (doc && doc->make_bookmark)
		return doc->make_bookmark(ctx, doc, loc);
	return (loc.chapter<<16) + loc.page;
}