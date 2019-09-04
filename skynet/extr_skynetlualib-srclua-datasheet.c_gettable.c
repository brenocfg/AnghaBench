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
typedef  int /*<<< orphan*/  uint32_t ;
struct table {int dummy; } ;
struct document {scalar_t__* index; int n; } ;

/* Variables and functions */
 scalar_t__ INVALID_OFFSET ; 

__attribute__((used)) static inline const struct table *
gettable(const struct document *doc, int index) {
	if (doc->index[index] == INVALID_OFFSET) {
		return NULL;
	}
	return (const struct table *)((const char *)doc + sizeof(uint32_t) + sizeof(uint32_t) + doc->n * sizeof(uint32_t) + doc->index[index]);
}