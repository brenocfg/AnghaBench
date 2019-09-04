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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  NUMPARSE ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONVERT (int,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  EXPECT_CY (int) ; 
 int /*<<< orphan*/  EXPECT_DECIMAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EXPECT_I1 (char) ; 
 int /*<<< orphan*/  EXPECT_I2 (short) ; 
 int /*<<< orphan*/  EXPECT_I4 (int) ; 
 int /*<<< orphan*/  EXPECT_I8 (int,int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  EXPECT_R4 (double) ; 
 int /*<<< orphan*/  EXPECT_R8 (double) ; 
 int /*<<< orphan*/  EXPECT_UI1 (int) ; 
 int /*<<< orphan*/  EXPECT_UI2 (int) ; 
 int NUMPRS_DECIMAL ; 
 int NUMPRS_EXPONENT ; 
 int NUMPRS_NEG ; 
 int /*<<< orphan*/  SETRGB (int,int) ; 
 int VTBIT_CY ; 
 int VTBIT_DECIMAL ; 
 int VTBIT_I1 ; 
 int VTBIT_I2 ; 
 int VTBIT_I4 ; 
 int VTBIT_I8 ; 
 int VTBIT_R4 ; 
 int VTBIT_R8 ; 
 int VTBIT_UI1 ; 
 int VTBIT_UI2 ; 
 int VTBIT_UI4 ; 
 int VTBIT_UI8 ; 
 int /*<<< orphan*/  VarNumFromParseNum ; 
 scalar_t__ has_i8 ; 

__attribute__((used)) static void test_VarNumFromParseNum(void)
{
  HRESULT hres;
  NUMPARSE np;
  BYTE rgb[128];
  VARIANT vOut;

  CHECKPTR(VarNumFromParseNum);
    
  /* Convert the number 1 to different types */
  SETRGB(0, 1); CONVERT(1,0,0,1,0,0, VTBIT_I1); EXPECT_I1(1);
  SETRGB(0, 1); CONVERT(1,0,0,1,0,0, VTBIT_UI1); EXPECT_UI1(1);
  /* Prefers a signed type to unsigned of the same size */
  SETRGB(0, 1); CONVERT(1,0,0,1,0,0, VTBIT_I1|VTBIT_UI1); EXPECT_I1(1);
  /* But takes the smaller size if possible */
  SETRGB(0, 1); CONVERT(1,0,0,1,0,0, VTBIT_I2|VTBIT_UI1); EXPECT_UI1(1);

  /* Try different integer sizes */
#define INTEGER_VTBITS (VTBIT_I1|VTBIT_UI1|VTBIT_I2|VTBIT_UI2|VTBIT_I4|VTBIT_UI4|VTBIT_I8|VTBIT_UI8)

  SETRGB(0, 1); CONVERT(1,0,0,1,0,0, INTEGER_VTBITS); EXPECT_I1(1);
  /* 127 */
  SETRGB(0, 1); SETRGB(1, 2); SETRGB(2, 7);
  CONVERT(3,0,0,3,0,0, INTEGER_VTBITS); EXPECT_I1(127);
  /* 128 */
  SETRGB(0, 1); SETRGB(1, 2); SETRGB(2, 8);
  CONVERT(3,0,0,3,0,0, INTEGER_VTBITS); EXPECT_UI1(128);
  /* 255 */
  SETRGB(0, 2); SETRGB(1, 5); SETRGB(2, 5);
  CONVERT(3,0,0,3,0,0, INTEGER_VTBITS); EXPECT_UI1(255);
  /* 256 */
  SETRGB(0, 2); SETRGB(1, 5); SETRGB(2, 6);
  CONVERT(3,0,0,3,0,0, INTEGER_VTBITS); EXPECT_I2(256);
  /* 32767 */
  SETRGB(0, 3); SETRGB(1, 2); SETRGB(2, 7); SETRGB(3, 6); SETRGB(4, 7);
  CONVERT(5,0,0,5,0,0, INTEGER_VTBITS); EXPECT_I2(32767);
  /* 32768 */
  SETRGB(0, 3); SETRGB(1, 2); SETRGB(2, 7); SETRGB(3, 6); SETRGB(4, 8);
  CONVERT(5,0,0,5,0,0, INTEGER_VTBITS); EXPECT_UI2(32768);

  /* Assume the above pattern holds for remaining positive integers; test negative */

  /* -128 */
  SETRGB(0, 1); SETRGB(1, 2); SETRGB(2, 8);
  CONVERT(3,0,NUMPRS_NEG,3,0,0, INTEGER_VTBITS); EXPECT_I1(-128);
  /* -129 */
  SETRGB(0, 1); SETRGB(1, 2); SETRGB(2, 9);
  CONVERT(3,0,NUMPRS_NEG,3,0,0, INTEGER_VTBITS); EXPECT_I2(-129);
  /* -32768 */
  SETRGB(0, 3); SETRGB(1, 2); SETRGB(2, 7); SETRGB(3, 6); SETRGB(4, 8);
  CONVERT(5,0,NUMPRS_NEG,5,0,0, INTEGER_VTBITS); EXPECT_I2(-32768);
  /* -32768 */
  SETRGB(0, 3); SETRGB(1, 2); SETRGB(2, 7); SETRGB(3, 6); SETRGB(4, 9);
  CONVERT(5,0,NUMPRS_NEG,5,0,0, INTEGER_VTBITS); EXPECT_I4(-32769);

  /* Assume the above pattern holds for remaining negative integers */

  /* Test hexadecimal conversions */
  SETRGB(0, 1); CONVERT(1,0,0,1,4,0, INTEGER_VTBITS); EXPECT_I1(0x01);
  /* 0x7f */
  SETRGB(0, 7); SETRGB(1, 0xf);
  CONVERT(2,0,0,2,4,0, INTEGER_VTBITS); EXPECT_I1(0x7f);
  SETRGB(0, 7); SETRGB(1, 0xf);
  CONVERT(2,0,0,2,4,0, VTBIT_DECIMAL); EXPECT_DECIMAL(0,0,0x7f);
  /* 0x7fff */
  SETRGB(0, 7); SETRGB(1, 0xf); SETRGB(2, 0xf); SETRGB(3, 0xf);
  CONVERT(4,0,0,4,4,0, INTEGER_VTBITS); EXPECT_I2(0x7fff);
  /* 0x7fffffff */
  SETRGB(0, 7); SETRGB(1, 0xf); SETRGB(2, 0xf); SETRGB(3, 0xf);
  SETRGB(4, 0xf); SETRGB(5, 0xf); SETRGB(6, 0xf); SETRGB(7, 0xf);
  CONVERT(8,0,0,8,4,0, INTEGER_VTBITS); EXPECT_I4(0x7fffffffL);
  /* 0x7fffffffffffffff (64 bits) */
  SETRGB(0, 7); SETRGB(1, 0xf); SETRGB(2, 0xf); SETRGB(3, 0xf);
  SETRGB(4, 0xf); SETRGB(5, 0xf); SETRGB(6, 0xf); SETRGB(7, 0xf);
  SETRGB(8, 0xf); SETRGB(9, 0xf); SETRGB(10, 0xf); SETRGB(11, 0xf);
  SETRGB(12, 0xf); SETRGB(13, 0xf); SETRGB(14, 0xf); SETRGB(15, 0xf);
  if (has_i8)
  {
    /* We cannot use INTEGER_VTBITS as WinXP and Win2003 are broken(?). They
       truncate the number to the smallest integer size requested:
       CONVERT(16,0,0,16,4,0, INTEGER_VTBITS); EXPECT_I1((signed char)0xff); */
    CONVERT(16,0,0,16,4,0, VTBIT_I8); EXPECT_I8(0x7fffffff,0xffffffff);
  }

  /* Assume the above pattern holds for numbers without hi-bit set, test (preservation of) hi-bit */
  /* 0x82 */
  SETRGB(0, 8); SETRGB(1, 2);
  CONVERT(2,0,0,2,4,0, INTEGER_VTBITS);
  EXPECT_I1((signed char)0x82);
  /* 0x8002 */
  SETRGB(0, 8); SETRGB(1, 0); SETRGB(2, 0); SETRGB(3, 2);
  CONVERT(4,0,0,4,4,0, INTEGER_VTBITS);
  EXPECT_I2((signed short)0x8002);
  /* 0x80000002 */
  SETRGB(0, 8); SETRGB(1, 0); SETRGB(2, 0); SETRGB(3, 0);
  SETRGB(4, 0); SETRGB(5, 0); SETRGB(6, 0); SETRGB(7, 2);
  CONVERT(8,0,0,8,4,0, INTEGER_VTBITS); EXPECT_I4(0x80000002);
  /* 0x8000000000000002 (64 bits) */
  SETRGB(0, 8); SETRGB(1, 0); SETRGB(2, 0); SETRGB(3, 0);
  SETRGB(4, 0); SETRGB(5, 0); SETRGB(6, 0); SETRGB(7, 0);
  SETRGB(8, 0); SETRGB(9, 0); SETRGB(10, 0); SETRGB(11, 0);
  SETRGB(12, 0); SETRGB(13, 0); SETRGB(14, 0); SETRGB(15, 2);
  if (has_i8)
  {
    /* We cannot use INTEGER_VTBITS as WinXP and Win2003 are broken(?). They
       truncate the number to the smallest integer size requested:
       CONVERT(16,0,0,16,4,0, INTEGER_VTBITS & ~VTBIT_I1);
       EXPECT_I2((signed short)0x0002); */
    CONVERT(16,0,0,16,4,0, VTBIT_I8); EXPECT_I8(0x80000000,0x00000002);
  }

  /* Test (preservation of) hi-bit with STRICT type requesting */
  /* 0x82 */
  SETRGB(0, 8); SETRGB(1, 2);
  CONVERT(2,0,0,2,4,0, VTBIT_I1);
  EXPECT_I1((signed char)0x82);
  /* 0x8002 */
  SETRGB(0, 8); SETRGB(1, 0); SETRGB(2, 0); SETRGB(3, 2);
  CONVERT(4,0,0,4,4,0, VTBIT_I2);
  EXPECT_I2((signed short)0x8002);
  /* 0x80000002 */
  SETRGB(0, 8); SETRGB(1, 0); SETRGB(2, 0); SETRGB(3, 0);
  SETRGB(4, 0); SETRGB(5, 0); SETRGB(6, 0); SETRGB(7, 2);
  CONVERT(8,0,0,8,4,0, VTBIT_I4); EXPECT_I4(0x80000002);
  /* 0x8000000000000002 (64 bits) */
  SETRGB(0, 8); SETRGB(1, 0); SETRGB(2, 0); SETRGB(3, 0);
  SETRGB(4, 0); SETRGB(5, 0); SETRGB(6, 0); SETRGB(7, 0);
  SETRGB(8, 0); SETRGB(9, 0); SETRGB(10, 0); SETRGB(11, 0);
  SETRGB(12, 0); SETRGB(13, 0); SETRGB(14, 0); SETRGB(15, 2);
  if (has_i8)
  {
    CONVERT(16,0,0,16,4,0, VTBIT_I8); EXPECT_I8(0x80000000,0x00000002);
  }
  /* Assume the above pattern holds for numbers with hi-bit set */

  /* Negative numbers overflow if we have only unsigned outputs */
  /* -1 */
  SETRGB(0, 1); CONVERT(1,0,NUMPRS_NEG,1,0,0, VTBIT_UI1); EXPECT_OVERFLOW;
  /* -0.6 */
  SETRGB(0, 6); CONVERT(1,0,NUMPRS_NEG,1,0,~0u, VTBIT_UI1); EXPECT_OVERFLOW;

  /* Except that rounding is done first, so -0.5 to 0 are accepted as 0 */
  /* -0.5 */
  SETRGB(0, 5); CONVERT(1,0,NUMPRS_NEG,1,0,~0u, VTBIT_UI1); EXPECT_UI1(0);

  /* Floating point zero is OK */
  /* 0.00000000E0 */
  SETRGB(0, 0); CONVERT(1,0,NUMPRS_DECIMAL|NUMPRS_EXPONENT,12,0,-8, VTBIT_R8);
  EXPECT_R8(0.0);

  /* Float is acceptable for an integer input value */
  SETRGB(0, 1); CONVERT(1,0,0,1,0,0, VTBIT_R4); EXPECT_R4(1.0f);
  /* As is double */
  SETRGB(0, 1); CONVERT(1,0,0,1,0,0, VTBIT_R8); EXPECT_R8(1.0);
  /* As is currency */
  SETRGB(0, 1); CONVERT(1,0,0,1,0,0, VTBIT_CY); EXPECT_CY(1);

  /* Float is preferred over double */
  SETRGB(0, 1); CONVERT(1,0,0,1,0,0, VTBIT_R4|VTBIT_R8); EXPECT_R4(1.0f);

  /* Double is preferred over currency */
  SETRGB(0, 1); CONVERT(1,0,0,1,0,0, VTBIT_R8|VTBIT_CY); EXPECT_R8(1.0);

  /* Currency is preferred over decimal */
  SETRGB(0, 1); CONVERT(1,0,0,1,0,0, VTBIT_CY|VTBIT_DECIMAL); EXPECT_CY(1);

  /* Underflow test */
  SETRGB(0, 1); CONVERT(1,0,NUMPRS_EXPONENT,1,0,-94938484, VTBIT_R4); EXPECT_R4(0.0);
  SETRGB(0, 1); CONVERT(1,0,NUMPRS_EXPONENT,1,0,-94938484, VTBIT_R8); EXPECT_R8(0.0);
  SETRGB(0, 1); CONVERT(1,0,NUMPRS_EXPONENT,1,0,-94938484, VTBIT_CY); EXPECT_CY(0);
}