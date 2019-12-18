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
struct TYPE_3__ {int mode; int /*<<< orphan*/  sha; int /*<<< orphan*/  crc64; int /*<<< orphan*/  crc; } ;
typedef  TYPE_1__ CXzCheck ;

/* Variables and functions */
 int /*<<< orphan*/  CRC64_INIT_VAL ; 
 int /*<<< orphan*/  CRC_INIT_VAL ; 
 int /*<<< orphan*/  Sha256_Init (int /*<<< orphan*/ *) ; 
#define  XZ_CHECK_CRC32 130 
#define  XZ_CHECK_CRC64 129 
#define  XZ_CHECK_SHA256 128 

void XzCheck_Init(CXzCheck *p, int mode)
{
  p->mode = mode;
  switch (mode)
  {
    case XZ_CHECK_CRC32: p->crc = CRC_INIT_VAL; break;
    case XZ_CHECK_CRC64: p->crc64 = CRC64_INIT_VAL; break;
    case XZ_CHECK_SHA256: Sha256_Init(&p->sha); break;
  }
}