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
struct triangulation_array {scalar_t__ count; struct triangulation* items; } ;
struct triangulation {int dummy; } ;
struct dynamic_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZeroMemory (struct triangulation*,int) ; 
 int /*<<< orphan*/  reserve (struct dynamic_array*,scalar_t__,int) ; 

__attribute__((used)) static struct triangulation *add_triangulation(struct triangulation_array *array)
{
    struct triangulation *item;

    if (!reserve((struct dynamic_array *)array, array->count + 1, sizeof(array->items[0])))
        return NULL;

    item = &array->items[array->count++];
    ZeroMemory(item, sizeof(*item));
    return item;
}