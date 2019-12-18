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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  aom_codec_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOM_ERR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ aom_codec_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_context(vlc_object_t *p_this, aom_codec_ctx_t *context)
{
    if (aom_codec_destroy(context))
        AOM_ERR(p_this, context, "Failed to destroy codec context");
}