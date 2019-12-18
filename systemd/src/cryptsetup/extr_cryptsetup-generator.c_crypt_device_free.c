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
struct TYPE_6__ {int /*<<< orphan*/  options; int /*<<< orphan*/  name; int /*<<< orphan*/  keydev; int /*<<< orphan*/  keyfile; int /*<<< orphan*/  uuid; } ;
typedef  TYPE_1__ crypto_device ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 

__attribute__((used)) static crypto_device* crypt_device_free(crypto_device *d) {
        if (!d)
                return NULL;

        free(d->uuid);
        free(d->keyfile);
        free(d->keydev);
        free(d->name);
        free(d->options);
        return mfree(d);
}