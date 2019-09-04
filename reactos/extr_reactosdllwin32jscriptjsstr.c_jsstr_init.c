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
typedef  unsigned int jsstr_tag_t ;
struct TYPE_3__ {unsigned int length_flags; int ref; } ;
typedef  TYPE_1__ jsstr_t ;

/* Variables and functions */
 unsigned int JSSTR_LENGTH_SHIFT ; 

__attribute__((used)) static inline void jsstr_init(jsstr_t *str, unsigned len, jsstr_tag_t tag)
{
    str->length_flags = len << JSSTR_LENGTH_SHIFT | tag;
    str->ref = 1;
}