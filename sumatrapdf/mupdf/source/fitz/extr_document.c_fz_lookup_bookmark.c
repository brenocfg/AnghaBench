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
typedef  int /*<<< orphan*/  fz_location ;
struct TYPE_4__ {int /*<<< orphan*/  (* lookup_bookmark ) (int /*<<< orphan*/ *,TYPE_1__*,int) ;} ;
typedef  TYPE_1__ fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int fz_bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  fz_make_location (int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

fz_location fz_lookup_bookmark(fz_context *ctx, fz_document *doc, fz_bookmark mark)
{
	if (doc && doc->lookup_bookmark)
		return doc->lookup_bookmark(ctx, doc, mark);
	return fz_make_location((mark>>16) & 0xffff, mark & 0xffff);
}