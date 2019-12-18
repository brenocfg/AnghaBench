#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int key_val_count; struct TYPE_4__* key_val; int /*<<< orphan*/  value; int /*<<< orphan*/  (* opj_free_func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ opj_tls_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opj_tls_destroy(opj_tls_t* tls)
{
    int i;
    if (!tls) {
        return;
    }
    for (i = 0; i < tls->key_val_count; i++) {
        if (tls->key_val[i].opj_free_func) {
            tls->key_val[i].opj_free_func(tls->key_val[i].value);
        }
    }
    opj_free(tls->key_val);
    opj_free(tls);
}