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
struct string {scalar_t__ len; char* data; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NC_ENOMEM ; 
 int /*<<< orphan*/  NC_OK ; 
 char* nc_strndup (char*,scalar_t__) ; 

rstatus_t
string_duplicate(struct string *dst, const struct string *src)
{
    ASSERT(dst->len == 0 && dst->data == NULL);
    ASSERT(src->len != 0 && src->data != NULL);

    dst->data = nc_strndup(src->data, src->len + 1);
    if (dst->data == NULL) {
        return NC_ENOMEM;
    }

    dst->len = src->len;
    dst->data[dst->len] = '\0';

    return NC_OK;
}