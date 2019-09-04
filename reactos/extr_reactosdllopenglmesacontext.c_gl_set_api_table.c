#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gl_api_table {int dummy; } ;
struct TYPE_3__ {struct gl_api_table const Exec; int /*<<< orphan*/  API; } ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ *,struct gl_api_table const*,int) ; 

void gl_set_api_table( GLcontext *ctx, const struct gl_api_table *api )
{
   if (api) {
      MEMCPY( &ctx->API, api, sizeof(struct gl_api_table) );
   }
   else {
      MEMCPY( &ctx->API, &ctx->Exec, sizeof(struct gl_api_table) );
   }
}