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
struct params_s {int /*<<< orphan*/  p_append; scalar_t__ i_append; int /*<<< orphan*/ * packets; int /*<<< orphan*/ * packets_sizes; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_CLEANUP (int,int /*<<< orphan*/ ) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int xiph_AppendHeaders (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_xiph_AppendHeaders(const char *run,
                 const uint8_t *p_extra, size_t i_extra,
                 struct params_s *source)
{
    int ret = xiph_AppendHeaders(&source->i_append, &source->p_append,
                                 source->packets_sizes[0], source->packets[0]);
    if(ret == VLC_SUCCESS)
    {
        EXPECT_CLEANUP((i_extra == (unsigned)source->i_append),
                       free(source->p_append));
        EXPECT_CLEANUP(!memcmp(p_extra, source->p_append, source->i_append),
                       free(source->p_append));
    }
    return ret;
}