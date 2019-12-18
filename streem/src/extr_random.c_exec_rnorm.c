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
struct rnorm_data {int /*<<< orphan*/  has_spare; int /*<<< orphan*/  seed; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int strm_int ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  free (struct rnorm_data*) ; 
 int /*<<< orphan*/  gen_rnorm ; 
 struct rnorm_data* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,char const**,int*) ; 
 int /*<<< orphan*/  strm_producer ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xorshift128init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_rnorm(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct rnorm_data* d;
  const char* s;
  strm_int len;

  strm_get_args(strm, argc, args, "|s", &s, &len);
  d = malloc(sizeof(struct rnorm_data));
  if (!d) return STRM_NG;
  if (argc == 2) {
    if (len != sizeof(d->seed)) {
      strm_raise(strm, "seed size differ");
      free(d);
      return STRM_NG;
    }
    memcpy(d->seed, s, len);
  }
  else {
    xorshift128init(d->seed);
  }
  d->has_spare = FALSE;
  *ret = strm_stream_value(strm_stream_new(strm_producer, gen_rnorm, NULL, (void*)d));
  return STRM_OK;
}