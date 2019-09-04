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
typedef  int /*<<< orphan*/  pagesetup_data ;
typedef  int LONG ;

/* Variables and functions */
 scalar_t__ is_metric (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline LONG thousandths_inch_to_size(const pagesetup_data *data, LONG size)
{
    if (is_metric(data))
        return size * 254 / 100;
    else
        return size;
}