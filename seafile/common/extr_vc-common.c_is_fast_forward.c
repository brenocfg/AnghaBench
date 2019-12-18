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
typedef  int gboolean ;
typedef  scalar_t__ VCCompareResult ;

/* Variables and functions */
 scalar_t__ VC_FAST_FORWARD ; 
 scalar_t__ vc_compare_commits (char const*,int,char const*,char const*) ; 

gboolean
is_fast_forward (const char *repo_id, int version,
                 const char *src_head, const char *dst_head)
{
    VCCompareResult res;

    res = vc_compare_commits (repo_id, version, src_head, dst_head);

    return (res == VC_FAST_FORWARD);
}