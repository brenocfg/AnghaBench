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
struct outline_array {scalar_t__ count; struct outline* items; } ;
struct outline {int dummy; } ;
struct dynamic_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZeroMemory (struct outline*,int) ; 
 int /*<<< orphan*/  reserve (struct dynamic_array*,scalar_t__,int) ; 

__attribute__((used)) static struct outline *add_outline(struct outline_array *array)
{
    struct outline *item;

    if (!reserve((struct dynamic_array *)array, array->count + 1, sizeof(array->items[0])))
        return NULL;

    item = &array->items[array->count++];
    ZeroMemory(item, sizeof(*item));
    return item;
}