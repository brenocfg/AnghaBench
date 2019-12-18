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
 int /*<<< orphan*/  utf8Read (unsigned char const*,int,int*) ; 

__attribute__((used)) static int utf8Charlen(const char *zIn, int nIn){
  int i;
  int nChar = 0;
  for(i=0; i<nIn; nChar++){
    int sz;
    utf8Read((const unsigned char *)&zIn[i], nIn-i, &sz);
    i += sz;
  }
  return nChar;
}