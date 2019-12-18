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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_BLOB ; 
 int /*<<< orphan*/  hash_sha1_file (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  typename (int) ; 

__attribute__((used)) static int index_mem(unsigned char *sha1, void *buf, uint64_t size,
                     enum object_type type, const char *path)
{
    if (!type)
        type = OBJ_BLOB;

    hash_sha1_file(buf, size, typename(type), sha1);
    return 0;
}