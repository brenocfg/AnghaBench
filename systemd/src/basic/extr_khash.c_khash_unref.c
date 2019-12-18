#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  algorithm; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ khash ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 

khash* khash_unref(khash *h) {
        if (!h)
                return NULL;

        safe_close(h->fd);
        free(h->algorithm);
        return mfree(h);
}