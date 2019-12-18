#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UInt64 ;
typedef  scalar_t__ CXzStreamFlags ;
typedef  int /*<<< orphan*/  Byte ;
typedef  int Bool ;

/* Variables and functions */
 scalar_t__ CrcCalc (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ GetBe16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ GetUi32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  XZ_FOOTER_SIG ; 
 int /*<<< orphan*/  XZ_FOOTER_SIG_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Bool Xz_CheckFooter(CXzStreamFlags flags, UInt64 indexSize, const Byte *buf)
{
  return
      indexSize == (((UInt64)GetUi32(buf + 4) + 1) << 2) &&
      (GetUi32(buf) == CrcCalc(buf + 4, 6) &&
      flags == GetBe16(buf + 8) &&
      memcmp(buf + 10, XZ_FOOTER_SIG, XZ_FOOTER_SIG_SIZE) == 0);
}