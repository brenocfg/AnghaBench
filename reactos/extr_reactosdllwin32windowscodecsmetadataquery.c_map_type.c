#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct string_t {scalar_t__ len; int /*<<< orphan*/  str; } ;
typedef  int /*<<< orphan*/  VARTYPE ;
typedef  size_t UINT ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  vt; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CompareStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  NORM_IGNORECASE ; 
 int /*<<< orphan*/  VT_ILLEGAL ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* str2vt ; 
 int /*<<< orphan*/  wine_dbgstr_wn (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static VARTYPE map_type(struct string_t *str)
{
    UINT i;

    for (i = 0; i < ARRAY_SIZE(str2vt); i++)
    {
        if (str2vt[i].len == str->len)
        {
            if (CompareStringW(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE,
                str->str, str->len, str2vt[i].str, str2vt[i].len) == CSTR_EQUAL)
                return str2vt[i].vt;
        }
    }

    WARN("type %s is not recognized\n", wine_dbgstr_wn(str->str, str->len));

    return VT_ILLEGAL;
}