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
struct TYPE_3__ {scalar_t__ use_threads; int /*<<< orphan*/  color_mode; } ;
typedef  TYPE_1__ WebPAnimDecoderOptions ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_RGBA ; 

__attribute__((used)) static void DefaultDecoderOptions(WebPAnimDecoderOptions* const dec_options) {
  dec_options->color_mode = MODE_RGBA;
  dec_options->use_threads = 0;
}