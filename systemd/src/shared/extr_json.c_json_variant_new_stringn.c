#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* string; } ;
typedef  TYPE_1__ JsonVariant ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__** IN_SET (size_t,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* JSON_VARIANT_MAGIC_EMPTY_STRING ; 
 int /*<<< orphan*/  JSON_VARIANT_STRING ; 
 int /*<<< orphan*/  assert_return (TYPE_1__**,int) ; 
 int json_variant_new (TYPE_1__**,int /*<<< orphan*/ ,size_t) ; 
 int json_variant_new_null (TYPE_1__**) ; 
 scalar_t__ memchr (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

int json_variant_new_stringn(JsonVariant **ret, const char *s, size_t n) {
        JsonVariant *v;
        int r;

        assert_return(ret, -EINVAL);
        if (!s) {
                assert_return(IN_SET(n, 0, (size_t) -1), -EINVAL);
                return json_variant_new_null(ret);
        }
        if (n == (size_t) -1) /* determine length automatically */
                n = strlen(s);
        else if (memchr(s, 0, n)) /* don't allow embedded NUL, as we can't express that in JSON */
                return -EINVAL;
        if (n == 0) {
                *ret = JSON_VARIANT_MAGIC_EMPTY_STRING;
                return 0;
        }

        r = json_variant_new(&v, JSON_VARIANT_STRING, n + 1);
        if (r < 0)
                return r;

        memcpy(v->string, s, n);
        v->string[n] = 0;

        *ret = v;
        return 0;
}