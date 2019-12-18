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
typedef  int /*<<< orphan*/  off64_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ftelli64 (void*) ; 
 int /*<<< orphan*/  ftell (void*) ; 
 int /*<<< orphan*/  ftello (void*) ; 

__attribute__((used)) static off64_t file_tell(void *data)
{
#ifdef _MSC_VER
    return _ftelli64(data);
#elif _POSIX_C_SOURCE >= 200112L
    return ftello(data);
#else
    return ftell(data);
#endif
}