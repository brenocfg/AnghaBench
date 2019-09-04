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
 int /*<<< orphan*/ * zipmapLookupRaw (unsigned char*,unsigned char*,unsigned int,int /*<<< orphan*/ *) ; 

int zipmapExists(unsigned char *zm, unsigned char *key, unsigned int klen) {
    return zipmapLookupRaw(zm,key,klen,NULL) != NULL;
}