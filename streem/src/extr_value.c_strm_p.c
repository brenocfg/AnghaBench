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
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_string ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 char* strm_str_cstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strm_to_str (int /*<<< orphan*/ ) ; 

const char*
strm_p(strm_value val)
{
  char buf[7];
  strm_string str = strm_to_str(val);
  const char* p = strm_str_cstr(str, buf);
  fputs(p, stdout);
  fputs("\n", stdout);
  return p;
}