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
struct TYPE_4__ {int /*<<< orphan*/  fmt_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void transcode_encoder_update_format_in( transcode_encoder_t *p_enc, const es_format_t *fmt )
{
    es_format_Clean( &p_enc->p_encoder->fmt_in );
    es_format_Copy( &p_enc->p_encoder->fmt_in, fmt );
}