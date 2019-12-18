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
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_nil_value () ; 
 int /*<<< orphan*/  strm_str_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_string_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_cputs(strm_stream* strm, FILE* out, int argc, strm_value* args, strm_value* ret)
{
  int i;

  for (i = 0; i < argc; i++) {
    strm_string s;

    if (i != 0) {
      if (!strm_string_p(args[i-1])) {
        fputs(" ", out);
      }
    }
    s = strm_to_str(args[i]);
    fwrite(strm_str_ptr(s), strm_str_len(s), 1, out);
  }
  fputs("\n", out);
  *ret = strm_nil_value();
  return STRM_OK;
}