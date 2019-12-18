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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int getbit (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ jbig2_find_changing_element (int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint32_t
jbig2_find_changing_element_of_color(const byte *line, uint32_t x, uint32_t w, int color)
{
    if (line == NULL)
        return w;
    x = jbig2_find_changing_element(line, x, w);
    if (x < w && getbit(line, x) != color)
        x = jbig2_find_changing_element(line, x, w);
    return x;
}