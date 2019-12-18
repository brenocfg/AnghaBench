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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* writer ) (int /*<<< orphan*/  const*,int,TYPE_1__ const* const) ;} ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int,TYPE_1__ const* const) ; 

__attribute__((used)) static int PutPaddingByte(const WebPPicture* const pic) {
  const uint8_t pad_byte[1] = { 0 };
  return !!pic->writer(pad_byte, 1, pic);
}