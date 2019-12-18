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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct string {size_t len; char* data; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NC_ENOMEM ; 
 int /*<<< orphan*/  NC_OK ; 
 char* nc_strndup (int /*<<< orphan*/  const*,scalar_t__) ; 

rstatus_t
string_copy(struct string *dst, const uint8_t *src, uint32_t srclen)
{
    ASSERT(dst->len == 0 && dst->data == NULL);
    ASSERT(src != NULL && srclen != 0);

    dst->data = nc_strndup(src, srclen + 1);
    if (dst->data == NULL) {
        return NC_ENOMEM;
    }

    dst->len = srclen;
    dst->data[dst->len] = '\0';

    return NC_OK;
}