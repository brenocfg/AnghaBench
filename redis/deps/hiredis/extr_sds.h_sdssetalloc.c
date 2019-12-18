#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  unsigned char* sds ;
struct TYPE_2__ {int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 TYPE_1__* SDS_HDR (int,unsigned char*) ; 
#define  SDS_TYPE_16 132 
#define  SDS_TYPE_32 131 
#define  SDS_TYPE_5 130 
#define  SDS_TYPE_64 129 
#define  SDS_TYPE_8 128 
 unsigned char SDS_TYPE_MASK ; 

__attribute__((used)) static inline void sdssetalloc(sds s, size_t newlen) {
    unsigned char flags = s[-1];
    switch(flags&SDS_TYPE_MASK) {
        case SDS_TYPE_5:
            /* Nothing to do, this type has no total allocation info. */
            break;
        case SDS_TYPE_8:
            SDS_HDR(8,s)->alloc = (uint8_t)newlen;
            break;
        case SDS_TYPE_16:
            SDS_HDR(16,s)->alloc = (uint16_t)newlen;
            break;
        case SDS_TYPE_32:
            SDS_HDR(32,s)->alloc = (uint32_t)newlen;
            break;
        case SDS_TYPE_64:
            SDS_HDR(64,s)->alloc = (uint64_t)newlen;
            break;
    }
}