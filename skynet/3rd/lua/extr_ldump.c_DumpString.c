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
typedef  int /*<<< orphan*/  TString ;
typedef  int /*<<< orphan*/  DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpByte (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpVar (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpVector (char const*,size_t,int /*<<< orphan*/ *) ; 
 int cast_int (size_t) ; 
 char* getstr (int /*<<< orphan*/  const*) ; 
 int tsslen (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void DumpString (const TString *s, DumpState *D) {
  if (s == NULL)
    DumpByte(0, D);
  else {
    size_t size = tsslen(s) + 1;  /* include trailing '\0' */
    const char *str = getstr(s);
    if (size < 0xFF)
      DumpByte(cast_int(size), D);
    else {
      DumpByte(0xFF, D);
      DumpVar(size, D);
    }
    DumpVector(str, size - 1, D);  /* no need to save '\0' */
  }
}