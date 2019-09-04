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
typedef  int /*<<< orphan*/  stb_ps ;

/* Variables and functions */
 int /*<<< orphan*/  GetArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetBucket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetHash (int /*<<< orphan*/ *) ; 
#define  STB_ps_array 131 
#define  STB_ps_bucket 130 
#define  STB_ps_direct 129 
#define  STB_ps_hash 128 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_bucket_free (int /*<<< orphan*/ ) ; 

void stb_ps_delete(stb_ps *ps)
{
    switch (3 & (int)(size_t) ps) {
      case STB_ps_direct: break;
      case STB_ps_bucket: stb_bucket_free(GetBucket(ps)); break;
      case STB_ps_array : free(GetArray(ps)); break;
      case STB_ps_hash  : free(GetHash(ps)); break;
   }
}