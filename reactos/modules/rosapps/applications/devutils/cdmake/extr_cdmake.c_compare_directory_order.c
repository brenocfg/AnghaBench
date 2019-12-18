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
struct TYPE_4__ {int /*<<< orphan*/  extension_on_cd; int /*<<< orphan*/  name_on_cd; } ;
typedef  TYPE_1__* PDIR_RECORD ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compare_directory_order(PDIR_RECORD p, PDIR_RECORD q)
{
    int n = strcmp(p->name_on_cd, q->name_on_cd);
    if (n == 0)
        n = strcmp(p->extension_on_cd, q->extension_on_cd);
    return n;
}