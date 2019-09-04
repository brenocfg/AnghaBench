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
struct TYPE_2__ {int id; int /*<<< orphan*/ * text; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 TYPE_1__* internal_errors ; 

__attribute__((used)) static LPCWSTR get_internal_error_message(int error)
{
    int i = 0;

    while (internal_errors[i].id != 0)
    {
        if (internal_errors[i].id == error)
            return internal_errors[i].text;
        i++;
    }

    FIXME("missing error message %d\n", error);
    return NULL;
}