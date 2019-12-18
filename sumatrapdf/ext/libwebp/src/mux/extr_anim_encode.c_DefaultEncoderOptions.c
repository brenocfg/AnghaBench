#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bgcolor; scalar_t__ loop_count; } ;
struct TYPE_6__ {scalar_t__ verbose; scalar_t__ allow_mixed; scalar_t__ minimize_size; TYPE_1__ anim_params; } ;
typedef  TYPE_2__ WebPAnimEncoderOptions ;

/* Variables and functions */
 int /*<<< orphan*/  DisableKeyframes (TYPE_2__* const) ; 

__attribute__((used)) static void DefaultEncoderOptions(WebPAnimEncoderOptions* const enc_options) {
  enc_options->anim_params.loop_count = 0;
  enc_options->anim_params.bgcolor = 0xffffffff;  // White.
  enc_options->minimize_size = 0;
  DisableKeyframes(enc_options);
  enc_options->allow_mixed = 0;
  enc_options->verbose = 0;
}