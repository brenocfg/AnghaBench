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
struct hpack_decoder {size_t max_size; scalar_t__ size; scalar_t__ entries; int /*<<< orphan*/ * table; } ;

/* Variables and functions */
 struct hpack_decoder* malloc (int) ; 

struct hpack_decoder *hpack_decode_init(size_t header_table_size)
{
    struct hpack_decoder *dec = malloc(sizeof (*dec));
    if (dec == NULL)
        return NULL;

    dec->table = NULL;
    dec->entries = 0;
    dec->size = 0;
    dec->max_size = header_table_size;
    return dec;
}