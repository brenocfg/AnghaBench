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
typedef  int uint8_t ;
typedef  int int8_t ;
typedef  int int64_t ;
typedef  int int32_t ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  i64 ;
typedef  int /*<<< orphan*/  i32 ;
typedef  int /*<<< orphan*/  i16 ;

/* Variables and functions */
 unsigned char ZIP_INT_16B ; 
 unsigned char ZIP_INT_24B ; 
 unsigned char ZIP_INT_32B ; 
 unsigned char ZIP_INT_64B ; 
 unsigned char ZIP_INT_8B ; 
 unsigned char ZIP_INT_IMM_MASK ; 
 unsigned char ZIP_INT_IMM_MAX ; 
 unsigned char ZIP_INT_IMM_MIN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char*,int) ; 
 int /*<<< orphan*/  memrev16ifbe (int*) ; 
 int /*<<< orphan*/  memrev32ifbe (int*) ; 
 int /*<<< orphan*/  memrev64ifbe (int*) ; 

int64_t zipLoadInteger(unsigned char *p, unsigned char encoding) {
    int16_t i16;
    int32_t i32;
    int64_t i64, ret = 0;
    if (encoding == ZIP_INT_8B) {
        ret = ((int8_t*)p)[0];
    } else if (encoding == ZIP_INT_16B) {
        memcpy(&i16,p,sizeof(i16));
        memrev16ifbe(&i16);
        ret = i16;
    } else if (encoding == ZIP_INT_32B) {
        memcpy(&i32,p,sizeof(i32));
        memrev32ifbe(&i32);
        ret = i32;
    } else if (encoding == ZIP_INT_24B) {
        i32 = 0;
        memcpy(((uint8_t*)&i32)+1,p,sizeof(i32)-sizeof(uint8_t));
        memrev32ifbe(&i32);
        ret = i32>>8;
    } else if (encoding == ZIP_INT_64B) {
        memcpy(&i64,p,sizeof(i64));
        memrev64ifbe(&i64);
        ret = i64;
    } else if (encoding >= ZIP_INT_IMM_MIN && encoding <= ZIP_INT_IMM_MAX) {
        ret = (encoding & ZIP_INT_IMM_MASK)-1;
    } else {
        assert(NULL);
    }
    return ret;
}