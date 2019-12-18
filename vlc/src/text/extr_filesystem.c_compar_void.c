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

/* Variables and functions */

__attribute__((used)) static int compar_void(const void *a, const void *b, void *data)
{
    const char *sa = a, *sb = b;
    int (*cmp)(const char **, const char **) = data;

    return cmp(&sa, &sb);
}