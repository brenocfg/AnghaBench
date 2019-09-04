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
typedef  int /*<<< orphan*/  zlexrangespec ;
typedef  int /*<<< orphan*/  sds ;

/* Variables and functions */
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ziplistGetObject (unsigned char*) ; 
 int zslLexValueLteMax (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int zzlLexValueLteMax(unsigned char *p, zlexrangespec *spec) {
    sds value = ziplistGetObject(p);
    int res = zslLexValueLteMax(value,spec);
    sdsfree(value);
    return res;
}