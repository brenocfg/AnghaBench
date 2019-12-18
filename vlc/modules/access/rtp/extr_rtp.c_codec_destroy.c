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
typedef  int /*<<< orphan*/  es_out_id_t ;
struct TYPE_3__ {int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void codec_destroy (demux_t *demux, void *data)
{
    if (data)
        es_out_Del (demux->out, (es_out_id_t *)data);
}