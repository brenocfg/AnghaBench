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
struct detail_data {int dummy; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  add_all_extensions (int /*<<< orphan*/ ,struct detail_data*) ; 
 int /*<<< orphan*/  add_properties (int /*<<< orphan*/ ,struct detail_data*) ; 
 int /*<<< orphan*/  add_v1_fields (int /*<<< orphan*/ ,struct detail_data*) ; 

__attribute__((used)) static void add_all_fields(HWND hwnd, struct detail_data *data)
{
    add_v1_fields(hwnd, data);
    add_all_extensions(hwnd, data);
    add_properties(hwnd, data);
}