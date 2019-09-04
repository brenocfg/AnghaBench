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
typedef  int /*<<< orphan*/  create_detailed_value_func ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_STRING_LEN ; 
 int /*<<< orphan*/  add_field_and_value_to_list (int /*<<< orphan*/ ,struct detail_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static void add_string_id_and_value_to_list(HWND hwnd, struct detail_data *data,
 int id, LPWSTR value, create_detailed_value_func create, void *param)
{
    WCHAR buf[MAX_STRING_LEN];

    LoadStringW(hInstance, id, buf, ARRAY_SIZE(buf));
    add_field_and_value_to_list(hwnd, data, buf, value, create, param);
}