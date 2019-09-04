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
struct pool {int dummy; } ;

/* Variables and functions */
 char* pool_alloc (struct pool*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

char* pool_strdup(struct pool* pool, const char* str)
{
    char* ret;
    if ((ret = pool_alloc(pool, strlen(str) + 1))) strcpy(ret, str);
    return ret;
}