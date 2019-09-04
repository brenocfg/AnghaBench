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
struct TYPE_3__ {int /*<<< orphan*/  rem_bytes; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ parse_buffer ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */

__attribute__((used)) static void rewind_bytes(parse_buffer * buf, DWORD size)
{
  buf->buffer -= size;
  buf->rem_bytes += size;
}