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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_open_accelerated_document (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

fz_document *
fz_open_document(fz_context *ctx, const char *filename)
{
	return fz_open_accelerated_document(ctx, filename, NULL);
}