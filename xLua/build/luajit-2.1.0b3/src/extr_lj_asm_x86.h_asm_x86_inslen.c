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
typedef  size_t uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_32 ; 
 int* map_op1 ; 
 int* map_op2 ; 

__attribute__((used)) static uint32_t asm_x86_inslen(const uint8_t* p)
{
  uint32_t result = 0;
  uint32_t prefixes = 0;
  uint32_t x = map_op1[*p];
  for (;;) {
    switch (x >> 4) {
    case 0: return result + x + (prefixes & 4);
    case 1: prefixes |= x; x = map_op1[*++p]; result++; break;
    case 2: x = map_op2[*++p]; break;
    case 3: p++; goto mrm;
    case 4: result -= (prefixes & 2);  /* fallthrough */
    case 5: return result + (x & 15);
    case 6:  /* Group 3. */
      if (p[1] & 0x38) x = 2;
      else if ((prefixes & 2) && (x == 0x66)) x = 4;
      goto mrm;
    case 7: /* VEX c4/c5. */
      if (LJ_32 && p[1] < 0xc0) {
	x = 2;
	goto mrm;
      }
      if (x == 0x70) {
	x = *++p & 0x1f;
	result++;
	if (x >= 2) {
	  p += 2;
	  result += 2;
	  goto mrm;
	}
      }
      p++;
      result++;
      x = map_op2[*++p];
      break;
    case 8: result -= (prefixes & 2);  /* fallthrough */
    case 9: mrm:  /* ModR/M and possibly SIB. */
      result += (x & 15);
      x = *++p;
      switch (x >> 6) {
      case 0: if ((x & 7) == 5) return result + 4; break;
      case 1: result++; break;
      case 2: result += 4; break;
      case 3: return result;
      }
      if ((x & 7) == 4) {
	result++;
	if (x < 0x40 && (p[1] & 7) == 5) result += 4;
      }
      return result;
    }
  }
}