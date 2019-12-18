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
struct TYPE_5__ {TYPE_1__* p_encoder; } ;
typedef  TYPE_2__ transcode_encoder_t ;
typedef  int /*<<< orphan*/  es_format_t ;
struct TYPE_4__ {int /*<<< orphan*/  const fmt_out; } ;

/* Variables and functions */

const es_format_t *transcode_encoder_format_out( const transcode_encoder_t *p_enc )
{
    return &p_enc->p_encoder->fmt_out;
}