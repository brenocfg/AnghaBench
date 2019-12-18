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
struct TYPE_4__ {scalar_t__ error; } ;
typedef  TYPE_1__ RedisModuleIO ;

/* Variables and functions */
 int /*<<< orphan*/  RM_Free (char*) ; 
 char* RM_LoadStringBuffer (TYPE_1__*,size_t*) ; 
 int /*<<< orphan*/  string2ld (char*,size_t,long double*) ; 

long double RM_LoadLongDouble(RedisModuleIO *io) {
    if (io->error) return 0;
    long double value;
    size_t len;
    char* str = RM_LoadStringBuffer(io,&len);
    if (!str) return 0;
    string2ld(str,len,&value);
    RM_Free(str);
    return value;
}