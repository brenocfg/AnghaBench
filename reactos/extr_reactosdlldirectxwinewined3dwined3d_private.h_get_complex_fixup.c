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
struct color_fixup_desc {scalar_t__ x_source; scalar_t__ y_source; scalar_t__ z_source; scalar_t__ w_source; } ;
typedef  enum complex_fixup { ____Placeholder_complex_fixup } complex_fixup ;

/* Variables and functions */
 scalar_t__ CHANNEL_SOURCE_COMPLEX1 ; 

__attribute__((used)) static inline enum complex_fixup get_complex_fixup(struct color_fixup_desc fixup)
{
    enum complex_fixup complex_fixup = 0;
    if (fixup.x_source == CHANNEL_SOURCE_COMPLEX1) complex_fixup |= (1u << 0);
    if (fixup.y_source == CHANNEL_SOURCE_COMPLEX1) complex_fixup |= (1u << 1);
    if (fixup.z_source == CHANNEL_SOURCE_COMPLEX1) complex_fixup |= (1u << 2);
    if (fixup.w_source == CHANNEL_SOURCE_COMPLEX1) complex_fixup |= (1u << 3);
    return complex_fixup;
}