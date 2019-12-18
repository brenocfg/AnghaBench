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
typedef  int /*<<< orphan*/  pa_context ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_context_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_strerror (int /*<<< orphan*/ ) ; 

void vlc_pa_error (vlc_object_t *obj, const char *msg, pa_context *ctx)
{
    msg_Err (obj, "%s: %s", msg, pa_strerror (pa_context_errno (ctx)));
}