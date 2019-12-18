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
typedef  int /*<<< orphan*/  uint8_t ;
struct write_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBINE_TYPE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TYPE_BOOLEAN ; 
 int /*<<< orphan*/  wb_push (struct write_block*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
wb_boolean(struct write_block *wb, int boolean) {
	uint8_t n = COMBINE_TYPE(TYPE_BOOLEAN , boolean ? 1 : 0);
	wb_push(wb, &n, 1);
}