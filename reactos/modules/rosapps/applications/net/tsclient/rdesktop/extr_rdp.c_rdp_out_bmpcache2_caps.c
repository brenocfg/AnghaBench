#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bitmap_cache_persist_enable; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 int BMPCACHE2_C0_CELLS ; 
 int BMPCACHE2_C1_CELLS ; 
 int BMPCACHE2_C2_CELLS ; 
 int BMPCACHE2_FLAG_PERSIST ; 
 int BMPCACHE2_NUM_PSTCELLS ; 
 int RDP_CAPLEN_BMPCACHE2 ; 
 int RDP_CAPSET_BMPCACHE2 ; 
 int /*<<< orphan*/  out_uint16_be (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8s (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pstcache_init (TYPE_1__*,int) ; 

__attribute__((used)) static void
rdp_out_bmpcache2_caps(RDPCLIENT * This, STREAM s)
{
	out_uint16_le(s, RDP_CAPSET_BMPCACHE2);
	out_uint16_le(s, RDP_CAPLEN_BMPCACHE2);

	out_uint16_le(s, This->bitmap_cache_persist_enable ? 2 : 0);	/* version */

	out_uint16_be(s, 3);	/* number of caches in this set */

	/* max cell size for cache 0 is 16x16, 1 = 32x32, 2 = 64x64, etc */
	out_uint32_le(s, BMPCACHE2_C0_CELLS);
	out_uint32_le(s, BMPCACHE2_C1_CELLS);
	if (pstcache_init(This, 2))
	{
		out_uint32_le(s, BMPCACHE2_NUM_PSTCELLS | BMPCACHE2_FLAG_PERSIST);
	}
	else
	{
		out_uint32_le(s, BMPCACHE2_C2_CELLS);
	}
	out_uint8s(s, 20);	/* other bitmap caches not used */
}