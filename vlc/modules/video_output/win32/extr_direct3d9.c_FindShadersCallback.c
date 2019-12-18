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
struct TYPE_3__ {char** values; char** descs; int count; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ enum_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ListShaders (TYPE_1__*) ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 

__attribute__((used)) static int FindShadersCallback(const char *name, char ***values, char ***descs)
{
    VLC_UNUSED(name);

    enum_context_t ctx = { NULL, NULL, 0 };

    ListShaders(&ctx);

    *values = ctx.values;
    *descs = ctx.descs;
    return ctx.count;

}