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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  scalar_t__ Jbig2Severity ;

/* Variables and functions */
 scalar_t__ JBIG2_SEVERITY_DEBUG ; 
 scalar_t__ JBIG2_SEVERITY_FATAL ; 
 scalar_t__ JBIG2_SEVERITY_INFO ; 
 scalar_t__ JBIG2_SEVERITY_WARNING ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
error_callback(void *data, const char *msg, Jbig2Severity severity, int32_t seg_idx)
{
	fz_context *ctx = data;
	if (severity == JBIG2_SEVERITY_FATAL)
		fz_warn(ctx, "jbig2dec error: %s (segment %d)", msg, seg_idx);
	else if (severity == JBIG2_SEVERITY_WARNING)
		fz_warn(ctx, "jbig2dec warning: %s (segment %d)", msg, seg_idx);
#ifndef NDEBUG
	else if (severity == JBIG2_SEVERITY_INFO)
		fz_warn(ctx, "jbig2dec info: %s (segment %d)", msg, seg_idx);
	else if (severity == JBIG2_SEVERITY_DEBUG)
		fz_warn(ctx, "jbig2dec debug: %s (segment %d)", msg, seg_idx);
#endif
}