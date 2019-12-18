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
typedef  char uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int u64; int /*<<< orphan*/  i; } ;
typedef  TYPE_1__ TValue ;
typedef  int StrScanFmt ;

/* Variables and functions */
 int STRSCAN_ERROR ; 
#define  STRSCAN_I64 131 
#define  STRSCAN_INT 130 
#define  STRSCAN_U32 129 
#define  STRSCAN_U64 128 

__attribute__((used)) static StrScanFmt strscan_oct(const uint8_t *p, TValue *o,
			      StrScanFmt fmt, int32_t neg, uint32_t dig)
{
  uint64_t x = 0;

  /* Scan octal digits. */
  if (dig > 22 || (dig == 22 && *p > '1')) return STRSCAN_ERROR;
  while (dig-- > 0) {
    if (!(*p >= '0' && *p <= '7')) return STRSCAN_ERROR;
    x = (x << 3) + (*p++ & 7);
  }

  /* Format-specific handling. */
  switch (fmt) {
  case STRSCAN_INT:
    if (x >= 0x80000000u+neg) fmt = STRSCAN_U32;
    /* fallthrough */
  case STRSCAN_U32:
    if ((x >> 32)) return STRSCAN_ERROR;
    o->i = neg ? -(int32_t)x : (int32_t)x;
    break;
  default:
  case STRSCAN_I64:
  case STRSCAN_U64:
    o->u64 = neg ? (uint64_t)-(int64_t)x : x;
    break;
  }
  return fmt;
}