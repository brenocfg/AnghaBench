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
typedef  char uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;
struct TYPE_4__ {int i; int u64; } ;
typedef  TYPE_1__ TValue ;
typedef  int StrScanFmt ;

/* Variables and functions */
 int STRSCAN_ERROR ; 
#define  STRSCAN_I64 131 
#define  STRSCAN_INT 130 
 int STRSCAN_NUM ; 
 int STRSCAN_OPT_C ; 
 int STRSCAN_OPT_TONUM ; 
#define  STRSCAN_U32 129 
#define  STRSCAN_U64 128 
 int U64x (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  c0000000 ; 
 int /*<<< orphan*/  strscan_double (int,TYPE_1__*,int,int) ; 

__attribute__((used)) static StrScanFmt strscan_hex(const uint8_t *p, TValue *o,
			      StrScanFmt fmt, uint32_t opt,
			      int32_t ex2, int32_t neg, uint32_t dig)
{
  uint64_t x = 0;
  uint32_t i;

  /* Scan hex digits. */
  for (i = dig > 16 ? 16 : dig ; i; i--, p++) {
    uint32_t d = (*p != '.' ? *p : *++p); if (d > '9') d += 9;
    x = (x << 4) + (d & 15);
  }

  /* Summarize rounding-effect of excess digits. */
  for (i = 16; i < dig; i++, p++)
    x |= ((*p != '.' ? *p : *++p) != '0'), ex2 += 4;

  /* Format-specific handling. */
  switch (fmt) {
  case STRSCAN_INT:
    if (!(opt & STRSCAN_OPT_TONUM) && x < 0x80000000u+neg) {
      o->i = neg ? -(int32_t)x : (int32_t)x;
      return STRSCAN_INT;  /* Fast path for 32 bit integers. */
    }
    if (!(opt & STRSCAN_OPT_C)) { fmt = STRSCAN_NUM; break; }
    /* fallthrough */
  case STRSCAN_U32:
    if (dig > 8) return STRSCAN_ERROR;
    o->i = neg ? -(int32_t)x : (int32_t)x;
    return STRSCAN_U32;
  case STRSCAN_I64:
  case STRSCAN_U64:
    if (dig > 16) return STRSCAN_ERROR;
    o->u64 = neg ? (uint64_t)-(int64_t)x : x;
    return fmt;
  default:
    break;
  }

  /* Reduce range, then convert to double. */
  if ((x & U64x(c0000000,0000000))) { x = (x >> 2) | (x & 3); ex2 += 2; }
  strscan_double(x, o, ex2, neg);
  return fmt;
}