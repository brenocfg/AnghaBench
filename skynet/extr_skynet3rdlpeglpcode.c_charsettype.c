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
typedef  int byte ;
typedef  int /*<<< orphan*/  Opcode ;

/* Variables and functions */
 int BITSPERCHAR ; 
 int CHARSETSIZE ; 
 int /*<<< orphan*/  IAny ; 
 int /*<<< orphan*/  IChar ; 
 int /*<<< orphan*/  IFail ; 
 int /*<<< orphan*/  ISet ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static Opcode charsettype (const byte *cs, int *c) {
  int count = 0;  /* number of characters in the set */
  int i;
  int candidate = -1;  /* candidate position for the singleton char */
  for (i = 0; i < CHARSETSIZE; i++) {  /* for each byte */
    int b = cs[i];
    if (b == 0) {  /* is byte empty? */
      if (count > 1)  /* was set neither empty nor singleton? */
        return ISet;  /* neither full nor empty nor singleton */
      /* else set is still empty or singleton */
    }
    else if (b == 0xFF) {  /* is byte full? */
      if (count < (i * BITSPERCHAR))  /* was set not full? */
        return ISet;  /* neither full nor empty nor singleton */
      else count += BITSPERCHAR;  /* set is still full */
    }
    else if ((b & (b - 1)) == 0) {  /* has byte only one bit? */
      if (count > 0)  /* was set not empty? */
        return ISet;  /* neither full nor empty nor singleton */
      else {  /* set has only one char till now; track it */
        count++;
        candidate = i;
      }
    }
    else return ISet;  /* byte is neither empty, full, nor singleton */
  }
  switch (count) {
    case 0: return IFail;  /* empty set */
    case 1: {  /* singleton; find character bit inside byte */
      int b = cs[candidate];
      *c = candidate * BITSPERCHAR;
      if ((b & 0xF0) != 0) { *c += 4; b >>= 4; }
      if ((b & 0x0C) != 0) { *c += 2; b >>= 2; }
      if ((b & 0x02) != 0) { *c += 1; }
      return IChar;
    }
    default: {
       assert(count == CHARSETSIZE * BITSPERCHAR);  /* full set */
       return IAny;
    }
  }
}