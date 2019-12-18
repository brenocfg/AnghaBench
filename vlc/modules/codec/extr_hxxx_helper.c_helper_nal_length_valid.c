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
struct hxxx_helper {int i_nal_length_size; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
helper_nal_length_valid(struct hxxx_helper *hh)
{
    return hh->i_nal_length_size == 1 || hh->i_nal_length_size == 2
        || hh->i_nal_length_size == 4;
}