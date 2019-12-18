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
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int strm_int ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  quick_median (int /*<<< orphan*/ *,int) ; 
 int strm_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
ary_median(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_value* buf;
  strm_value* p;
  strm_int len;
  strm_value func;
  strm_int i;

  strm_get_args(strm, argc, args, "a|v", &p, &len, &func);

  if (len == 0) {
    strm_raise(strm, "empty array");
    return STRM_NG;
  }
  buf = malloc(sizeof(strm_value)*len);
  if (!buf) return STRM_NG;
  if (argc == 1) {              /* median(ary) */
    memcpy(buf, p, sizeof(strm_value)*len);
  }
  else {                        /* median(ary,func) */
    strm_value func = args[1];

    for (i=0; i<len; i++) {
      if (strm_funcall(strm, func, 1, &p[i], &buf[i]) == STRM_NG) {
        free(buf);
        return STRM_NG;
      }
    }
  }
  *ret = quick_median(buf, len);
  free(buf);
  return STRM_OK;
}