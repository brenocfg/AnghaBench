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
typedef  int /*<<< orphan*/  context_t ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;

/* Variables and functions */
 int /*<<< orphan*/  Context_Free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Collection_releaseContext(WINECRYPT_CERTSTORE *store, context_t *context)
{
    /* We don't cache context links, so just free them. */
    Context_Free(context);
}