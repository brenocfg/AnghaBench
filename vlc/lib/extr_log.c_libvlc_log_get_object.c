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
struct TYPE_3__ {char* psz_object_type; char* psz_header; uintptr_t i_object_id; } ;
typedef  TYPE_1__ libvlc_log_t ;

/* Variables and functions */

void libvlc_log_get_object(const libvlc_log_t *ctx,
                           const char **restrict name,
                           const char **restrict header,
                           uintptr_t *restrict id)
{
    if (name != NULL)
        *name = (ctx->psz_object_type != NULL)
                ? ctx->psz_object_type : "generic";
    if (header != NULL)
        *header = ctx->psz_header;
    if (id != NULL)
        *id = ctx->i_object_id;
}