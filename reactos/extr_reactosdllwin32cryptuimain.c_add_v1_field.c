#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v1_field {int /*<<< orphan*/  create_detailed_value; int /*<<< orphan*/  id; int /*<<< orphan*/ * (* format ) (int /*<<< orphan*/ ) ;} ;
struct detail_data {TYPE_1__* pCertViewInfo; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  pCertContext; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_string_id_and_value_to_list (int /*<<< orphan*/ ,struct detail_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_v1_field(HWND hwnd, struct detail_data *data,
 const struct v1_field *field)
{
    WCHAR *val = field->format(data->pCertViewInfo->pCertContext);

    if (val)
    {
        add_string_id_and_value_to_list(hwnd, data, field->id, val,
         field->create_detailed_value, NULL);
        HeapFree(GetProcessHeap(), 0, val);
    }
}