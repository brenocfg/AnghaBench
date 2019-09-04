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
struct TYPE_3__ {int /*<<< orphan*/  imalloc; } ;
typedef  TYPE_1__ xmlwriteroutput ;

/* Variables and functions */
 void* m_alloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void *writeroutput_alloc(xmlwriteroutput *output, size_t len)
{
    return m_alloc(output->imalloc, len);
}