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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int Uinttype ;
typedef  int /*<<< orphan*/  Inttype ;

/* Variables and functions */
 int BIG ; 

__attribute__((used)) static lua_Number getinteger (const char *buff, int endian,
                        int issigned, int size) {
  Uinttype l = 0;
  int i;
  if (endian == BIG) {
    for (i = 0; i < size; i++) {
      l <<= 8;
      l |= (Uinttype)(unsigned char)buff[i];
    }
  }
  else {
    for (i = size - 1; i >= 0; i--) {
      l <<= 8;
      l |= (Uinttype)(unsigned char)buff[i];
    }
  }
  if (!issigned)
    return (lua_Number)l;
  else {  /* signed format */
    Uinttype mask = (Uinttype)(~((Uinttype)0)) << (size*8 - 1);
    if (l & mask)  /* negative value? */
      l |= mask;  /* signal extension */
    return (lua_Number)(Inttype)l;
  }
}