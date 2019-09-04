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
struct color_fixup_desc {scalar_t__ x_source; } ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CHANNEL_SOURCE_COMPLEX0 ; 
 scalar_t__ CHANNEL_SOURCE_COMPLEX1 ; 

__attribute__((used)) static inline BOOL is_complex_fixup(struct color_fixup_desc fixup)
{
    return fixup.x_source == CHANNEL_SOURCE_COMPLEX0 || fixup.x_source == CHANNEL_SOURCE_COMPLEX1;
}