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
struct params_s {unsigned int packets_count; void const** packets; unsigned int* packets_sizes; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT (int) ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int SplitCompare(const char *run,
                        unsigned packet_size[],
                        const void *packet[], unsigned packet_count,
                        const struct params_s *source)
{
    EXPECT(source->packets_count == packet_count);
    for(unsigned i=0; i<packet_count; i++)
    {
        EXPECT(source->packets[i] == packet[i]);
        EXPECT(source->packets_sizes[i] == packet_size[i]);
    }
    return VLC_SUCCESS;
}