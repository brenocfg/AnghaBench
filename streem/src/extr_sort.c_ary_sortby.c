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
struct sortby_value {int /*<<< orphan*/  o; int /*<<< orphan*/  v; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int strm_int ;
typedef  int /*<<< orphan*/  strm_array ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  free (struct sortby_value*) ; 
 struct sortby_value* malloc (int) ; 
 int /*<<< orphan*/  qsort (struct sortby_value*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sortby_cmp ; 
 int /*<<< orphan*/  strm_ary_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strm_ary_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_ary_value (int /*<<< orphan*/ ) ; 
 int strm_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ary_sortby(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct sortby_value* buf;
  strm_value* p;
  strm_int len;
  strm_value func;
  strm_array ary;
  strm_int i;

  strm_get_args(strm, argc, args, "av", &p, &len, &func);

  buf = malloc(sizeof(struct sortby_value)*len);
  if (!buf) return STRM_NG;
  for (i=0; i<len; i++) {
    buf[i].o = p[i];
    if (strm_funcall(strm, func, 1, &p[i], &buf[i].v) == STRM_NG) {
      free(buf);
      return STRM_NG;;
    }
  }
  qsort(buf, len, sizeof(struct sortby_value), sortby_cmp);
  ary = strm_ary_new(NULL, len);
  p = strm_ary_ptr(ary);
  for (i=0; i<len; i++) {
    p[i] = buf[i].o;
  }
  free(buf);
  *ret = strm_ary_value(ary);
  return STRM_OK;
}