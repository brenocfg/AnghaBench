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
struct TYPE_3__ {char* p; size_t n; } ;
typedef  TYPE_1__ _gostring_ ;

/* Variables and functions */
 scalar_t__ _swig_goallocate (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static _gostring_ _swig_makegostring(const char *p, size_t l) {
  _gostring_ ret;
  ret.p = (char*)_swig_goallocate(l + 1);
  memcpy(ret.p, p, l);
  ret.n = l;
  return ret;
}