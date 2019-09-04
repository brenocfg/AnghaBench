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
typedef  int BOOL ;

/* Variables and functions */
 int PSD_INHUNDREDTHSOFMILLIMETERS ; 
 int pagesetup_get_flags (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline BOOL is_metric(const pagesetup_data *data)
{
    return pagesetup_get_flags(data) & PSD_INHUNDREDTHSOFMILLIMETERS;
}