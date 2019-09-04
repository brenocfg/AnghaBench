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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct TYPE_3__ {int /*<<< orphan*/ * symbols; } ;
typedef  TYPE_1__ FSE_dtable ;

/* Variables and functions */

__attribute__((used)) static inline u8 FSE_peek_symbol(const FSE_dtable *const dtable,
                                 const u16 state) {
    return dtable->symbols[state];
}