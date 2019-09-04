#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
struct TYPE_4__ {int len; } ;
typedef  TYPE_1__ FORMSTR ;
typedef  int /*<<< orphan*/  FORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  get_formstr_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* msi_alloc (int) ; 

__attribute__((used)) static WCHAR *dup_formstr( FORMAT *format, FORMSTR *str, int *ret_len )
{
    WCHAR *val;

    if (!str->len) return NULL;
    if ((val = msi_alloc( (str->len + 1) * sizeof(WCHAR) )))
    {
        memcpy( val, get_formstr_data(format, str), str->len * sizeof(WCHAR) );
        val[str->len] = 0;
        *ret_len = str->len;
    }
    return val;
}