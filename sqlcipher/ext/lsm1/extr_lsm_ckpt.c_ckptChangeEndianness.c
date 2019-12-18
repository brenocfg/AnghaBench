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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BYTESWAP32 (int /*<<< orphan*/ ) ; 
 scalar_t__ LSM_LITTLE_ENDIAN ; 

__attribute__((used)) static void ckptChangeEndianness(u32 *aInt, int nInt){
  if( LSM_LITTLE_ENDIAN ){
    int i;
    for(i=0; i<nInt; i++) aInt[i] = BYTESWAP32(aInt[i]);
  }
}