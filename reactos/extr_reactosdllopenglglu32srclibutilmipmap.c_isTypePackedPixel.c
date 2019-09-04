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
typedef  scalar_t__ GLenum ;
typedef  int GLboolean ;

/* Variables and functions */
 scalar_t__ GL_UNSIGNED_BYTE_2_3_3_REV ; 
 scalar_t__ GL_UNSIGNED_BYTE_3_3_2 ; 
 scalar_t__ GL_UNSIGNED_INT_10_10_10_2 ; 
 scalar_t__ GL_UNSIGNED_INT_2_10_10_10_REV ; 
 scalar_t__ GL_UNSIGNED_INT_8_8_8_8 ; 
 scalar_t__ GL_UNSIGNED_INT_8_8_8_8_REV ; 
 scalar_t__ GL_UNSIGNED_SHORT_1_5_5_5_REV ; 
 scalar_t__ GL_UNSIGNED_SHORT_4_4_4_4 ; 
 scalar_t__ GL_UNSIGNED_SHORT_4_4_4_4_REV ; 
 scalar_t__ GL_UNSIGNED_SHORT_5_5_5_1 ; 
 scalar_t__ GL_UNSIGNED_SHORT_5_6_5 ; 
 scalar_t__ GL_UNSIGNED_SHORT_5_6_5_REV ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legalType (scalar_t__) ; 

__attribute__((used)) static GLboolean isTypePackedPixel(GLenum type)
{
   assert(legalType(type));

   if (type == GL_UNSIGNED_BYTE_3_3_2 ||
       type == GL_UNSIGNED_BYTE_2_3_3_REV ||
       type == GL_UNSIGNED_SHORT_5_6_5 ||
       type == GL_UNSIGNED_SHORT_5_6_5_REV ||
       type == GL_UNSIGNED_SHORT_4_4_4_4 ||
       type == GL_UNSIGNED_SHORT_4_4_4_4_REV ||
       type == GL_UNSIGNED_SHORT_5_5_5_1 ||
       type == GL_UNSIGNED_SHORT_1_5_5_5_REV ||
       type == GL_UNSIGNED_INT_8_8_8_8 ||
       type == GL_UNSIGNED_INT_8_8_8_8_REV ||
       type == GL_UNSIGNED_INT_10_10_10_2 ||
       type == GL_UNSIGNED_INT_2_10_10_10_REV) {
      return 1;
   }
   else return 0;
}