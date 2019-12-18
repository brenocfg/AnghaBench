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
typedef  int UInt32 ;
struct TYPE_3__ {int /*<<< orphan*/  state; scalar_t__* buffer; } ;
typedef  TYPE_1__ CSha256 ;

/* Variables and functions */
 int /*<<< orphan*/  Sha256_Transform (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void Sha256_WriteByteBlock(CSha256 *p)
{
  UInt32 data32[16];
  unsigned i;
  for (i = 0; i < 16; i++)
    data32[i] =
      ((UInt32)(p->buffer[i * 4    ]) << 24) +
      ((UInt32)(p->buffer[i * 4 + 1]) << 16) +
      ((UInt32)(p->buffer[i * 4 + 2]) <<  8) +
      ((UInt32)(p->buffer[i * 4 + 3]));
  Sha256_Transform(p->state, data32);
}