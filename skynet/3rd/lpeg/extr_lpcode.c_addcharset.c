#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_2__ {int /*<<< orphan*/ * buff; } ;
typedef  int /*<<< orphan*/  CompileState ;

/* Variables and functions */
 scalar_t__ CHARSETINSTSIZE ; 
 int gethere (int /*<<< orphan*/ *) ; 
 TYPE_1__ getinstr (int /*<<< orphan*/ *,int) ; 
 size_t j ; 
 int /*<<< orphan*/  loopset (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nextinstruction (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void addcharset (CompileState *compst, const byte *cs) {
  int p = gethere(compst);
  int i;
  for (i = 0; i < (int)CHARSETINSTSIZE - 1; i++)
    nextinstruction(compst);  /* space for buffer */
  /* fill buffer with charset */
  loopset(j, getinstr(compst, p).buff[j] = cs[j]);
}