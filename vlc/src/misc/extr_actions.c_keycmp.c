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
struct mapping {scalar_t__ key; } ;

/* Variables and functions */

__attribute__((used)) static int keycmp (const void *a, const void *b)
{
    const struct mapping *ka = a, *kb = b;

    return (ka->key < kb->key) ? -1 : (ka->key > kb->key) ? +1 : 0;
}