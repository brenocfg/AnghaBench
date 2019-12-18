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
typedef  TYPE_1__* j_common_ptr ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int /*<<< orphan*/ * client_data; } ;

/* Variables and functions */
 int /*<<< orphan*/ * JZ_CTX_FROM_CINFO (TYPE_1__*) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fz_jpg_mem_term(j_common_ptr cinfo)
{
	if (cinfo->client_data)
	{
		fz_context *ctx = JZ_CTX_FROM_CINFO(cinfo);
		fz_free(ctx, cinfo->client_data);
		cinfo->client_data = NULL;
	}
}