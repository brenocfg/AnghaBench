#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int key_val_count; TYPE_1__* key_val; } ;
typedef  TYPE_2__ opj_tls_t ;
struct TYPE_4__ {int key; void* value; } ;

/* Variables and functions */

void* opj_tls_get(opj_tls_t* tls, int key)
{
    int i;
    for (i = 0; i < tls->key_val_count; i++) {
        if (tls->key_val[i].key == key) {
            return tls->key_val[i].value;
        }
    }
    return NULL;
}