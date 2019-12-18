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
typedef  int /*<<< orphan*/  uint8_t ;
struct params_s {int /*<<< orphan*/  packets_count; int /*<<< orphan*/  packets; scalar_t__ packets_sizes; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_CLEANUP (int,int /*<<< orphan*/ ) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,void*,size_t) ; 
 int xiph_PackHeaders (int*,void**,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_xiph_PackHeaders(const char *run,
                 const uint8_t *p_extra, size_t i_extra,
                 const struct params_s *source)
{
    void *p_result;
    int i_result;

    int ret = xiph_PackHeaders(&i_result, &p_result,
                               (unsigned *) source->packets_sizes,
                               source->packets, source->packets_count);
    if(ret == VLC_SUCCESS)
    {
        EXPECT_CLEANUP((i_extra == (unsigned)i_result), free(p_result));
        EXPECT_CLEANUP(!memcmp(p_extra, p_result, i_extra), free(p_result));
        free(p_result);
    }
    return ret;
}