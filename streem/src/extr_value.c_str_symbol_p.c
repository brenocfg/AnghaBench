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
typedef  int /*<<< orphan*/  strm_string ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  isalnum (int) ; 
 int /*<<< orphan*/  isalpha (int) ; 
 int strm_str_len (int /*<<< orphan*/ ) ; 
 char* strm_str_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
str_symbol_p(strm_string str)
{
  const char* p = strm_str_ptr(str);
  const char* pend = p + strm_str_len(str);

  if (!isalpha((int)*p) && *p != '_')
    return FALSE;
  p++;
  while (p<pend) {
    if (!isalnum((int)*p) && *p != '_')
      return FALSE;
    p++;
  }
  return TRUE;
}