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
struct TYPE_4__ {int /*<<< orphan*/  len_compressed_output; int /*<<< orphan*/  len_uncompressed_input; int /*<<< orphan*/  mark_frame_arg; int /*<<< orphan*/  (* mark_frame ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ bits_in_buf; } ;
typedef  TYPE_1__ lzx_data ;

/* Variables and functions */
 int /*<<< orphan*/  lzx_write_bits (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lzx_align_output(lzx_data *lzxd)
{
  if (lzxd->bits_in_buf) {
    lzx_write_bits(lzxd, 16 - lzxd->bits_in_buf, 0);
  }
  if (lzxd->mark_frame)
    lzxd->mark_frame(lzxd->mark_frame_arg, lzxd->len_uncompressed_input, lzxd->len_compressed_output);
}