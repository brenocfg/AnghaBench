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
struct string_map_iterator {int (* fn ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
string_map_iterate(void **slot, void *data)
{
	struct string_map_iterator *iterator = data;

	return iterator->fn(iterator->data, *slot);
}