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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int /*<<< orphan*/  seed ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_str_new (char const*,int) ; 
 int /*<<< orphan*/  xorshift128init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rand_seed(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  uint32_t seed[4];

  strm_get_args(strm, argc, args, "");
  xorshift128init(seed);
  *ret = strm_str_new((const char*)seed, sizeof(seed));
  return STRM_OK;
}