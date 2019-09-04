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
typedef  int /*<<< orphan*/  xmlreader ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* reader_alloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static inline void *reader_alloc_zero(xmlreader *reader, size_t len)
{
    void *ret = reader_alloc(reader, len);
    if (ret)
        memset(ret, 0, len);
    return ret;
}