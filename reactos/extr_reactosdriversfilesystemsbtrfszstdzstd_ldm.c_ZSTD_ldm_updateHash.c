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
typedef  int U64 ;
typedef  int BYTE ;

/* Variables and functions */
 int LDM_HASH_CHAR_OFFSET ; 
 int prime8bytes ; 

__attribute__((used)) static U64 ZSTD_ldm_updateHash(U64 hash, BYTE toRemove, BYTE toAdd, U64 hashPower)
{
    hash -= ((toRemove + LDM_HASH_CHAR_OFFSET) * hashPower);
    hash *= prime8bytes;
    hash += toAdd + LDM_HASH_CHAR_OFFSET;
    return hash;
}