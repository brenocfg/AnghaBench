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
struct csv_data {char sep; scalar_t__ n; int /*<<< orphan*/  prev; int /*<<< orphan*/ * types; int /*<<< orphan*/  headers; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 struct csv_data* malloc (int) ; 
 int /*<<< orphan*/  strm_ary_null ; 
 int /*<<< orphan*/  strm_filter ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_str_null ; 
 int /*<<< orphan*/ * strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sv_accept ; 
 int /*<<< orphan*/  sv_finish ; 

__attribute__((used)) static int
sv(strm_stream* strm, int argc, strm_value* args, strm_value* ret, char sep)
{
  strm_stream *t;
  struct csv_data *cd;

  strm_get_args(strm, argc, args, "");
  cd = malloc(sizeof(struct csv_data));
  if (!cd) return STRM_NG;
  cd->headers = strm_ary_null;
  cd->types = NULL;
  cd->prev = strm_str_null;
  cd->sep = sep;
  cd->n = 0;

  t = strm_stream_new(strm_filter, sv_accept, sv_finish, (void*)cd);
  *ret = strm_stream_value(t);
  return STRM_OK;
}