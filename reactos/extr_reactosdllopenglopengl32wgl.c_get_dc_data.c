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
struct wgl_dc_data {int dummy; } ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 struct wgl_dc_data* get_dc_data_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
struct wgl_dc_data*
get_dc_data(HDC hdc)
{
    return get_dc_data_ex(hdc, 0, 0, NULL);
}