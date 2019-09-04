#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int key_len; void const* key; } ;
typedef  TYPE_1__ sqliterk_cipher_conf ;

/* Variables and functions */

void sqliterk_cipher_conf_set_key(sqliterk_cipher_conf *conf, const void* key, int key_len)
{
    if (conf != NULL) {
        conf->key = key;
        conf->key_len = key_len;
    }
}