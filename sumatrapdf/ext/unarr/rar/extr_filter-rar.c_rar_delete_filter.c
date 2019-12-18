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
struct RARFilter {struct RARFilter* globaldata; struct RARFilter* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct RARFilter*) ; 

__attribute__((used)) static void rar_delete_filter(struct RARFilter *filter)
{
    while (filter) {
        struct RARFilter *next = filter->next;
        free(filter->globaldata);
        free(filter);
        filter = next;
    }
}