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

/* Variables and functions */
 scalar_t__ _mbsinc (unsigned char const*) ; 
 size_t _mbslen (unsigned char const*) ; 
 scalar_t__ _mbsncmp (unsigned char const*,unsigned char const*,size_t) ; 

unsigned char *_mbsstr(const unsigned char *src1,const unsigned char *src2)
{
  size_t len;

  if (src2 ==NULL || *src2 == 0)
    return (unsigned char *)src1;

  len = _mbslen(src2);

  while(*src1)
    {
      if ((*src1 == *src2) && (_mbsncmp(src1,src2,len) == 0))
	return (unsigned char *)src1;
      src1 = (unsigned char *)_mbsinc(src1);
    }
  return NULL;
}