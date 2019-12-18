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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  FSE_DStream_t ;

/* Variables and functions */
 size_t FSE_lookBits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSE_skipBits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t FSE_readBits(FSE_DStream_t* bitD, U32 nbBits)
{
    size_t value = FSE_lookBits(bitD, nbBits);
    FSE_skipBits(bitD, nbBits);
    return value;
}