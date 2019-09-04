#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int nBuffer; int nLen; scalar_t__ szData; } ;
typedef  TYPE_1__ ME_String ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 

void ME_StrDeleteV(ME_String *s, int nVChar, int nChars)
{
  int end_ofs = nVChar + nChars;

  assert(s->nBuffer); /* Not a const string */
  assert(nChars >= 0);
  assert(nVChar >= 0);
  assert(end_ofs <= s->nLen);

  memmove(s->szData + nVChar, s->szData + end_ofs,
          (s->nLen - end_ofs + 1) * sizeof(WCHAR));
  s->nLen -= nChars;
}