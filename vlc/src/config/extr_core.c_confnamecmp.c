#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ module_config_t ;

/* Variables and functions */
 int strcmp (void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int confnamecmp (const void *key, const void *elem)
{
    const module_config_t *const *conf = elem;

    return strcmp (key, (*conf)->psz_name);
}