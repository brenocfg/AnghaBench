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
struct TYPE_3__ {int length_flags; } ;
typedef  TYPE_1__ jsstr_t ;

/* Variables and functions */
 int JSSTR_LENGTH_SHIFT ; 

__attribute__((used)) static inline unsigned jsstr_length(jsstr_t *str)
{
    return str->length_flags >> JSSTR_LENGTH_SHIFT;
}