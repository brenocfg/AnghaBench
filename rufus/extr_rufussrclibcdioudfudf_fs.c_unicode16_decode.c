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

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  cdio_charset_to_utf8 (char*,int,char**,char*) ; 

__attribute__((used)) static char*
unicode16_decode(const uint8_t *data, int i_len)
{
  int i;
  char* r = NULL;

  switch (data[0])
  {
  case 8:
    r = (char*)calloc(i_len, 1);
    if (r == NULL)
      return r;
    for (i=0; i<i_len-1; i++)
      r[i] = data[i+1];
    return r;
  case 16:
    cdio_charset_to_utf8((char*)&data[1], i_len-1, &r, "UCS-2BE");
    return r;
  default:
    /* Empty string, as some existing sections can't take a NULL pointer */
    r = (char*)calloc(1, 1);
    return r;
  }
}