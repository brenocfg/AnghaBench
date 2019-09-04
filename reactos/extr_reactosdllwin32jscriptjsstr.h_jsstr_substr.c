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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/ * jsstr_alloc_buf (unsigned int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsstr_extract (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline jsstr_t *jsstr_substr(jsstr_t *str, unsigned off, unsigned len)
{
    jsstr_t *ret;
    WCHAR *ptr;

    ret = jsstr_alloc_buf(len, &ptr);
    if(ret)
        jsstr_extract(str, off, len, ptr);
    return ret;
}