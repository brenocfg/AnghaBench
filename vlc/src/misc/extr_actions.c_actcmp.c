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
struct name2action {int /*<<< orphan*/  psz; } ;

/* Variables and functions */
 int strcmp (void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int actcmp(const void *key, const void *ent)
{
    const struct name2action *act = ent;
    return strcmp(key, act->psz);
}