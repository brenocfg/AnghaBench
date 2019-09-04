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
typedef  int U32 ;

/* Variables and functions */
 int prime5bytes ; 

__attribute__((used)) static size_t ZSTD_hash5(U64 u, U32 h) { return (size_t)(((u << (64 - 40)) * prime5bytes) >> (64 - h)); }