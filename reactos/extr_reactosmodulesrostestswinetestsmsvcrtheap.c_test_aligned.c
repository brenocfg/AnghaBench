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
typedef  int /*<<< orphan*/ * HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/ * GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 void* p_aligned_free ; 
 void* p_aligned_malloc ; 
 void* p_aligned_offset_malloc ; 
 void* p_aligned_offset_realloc ; 
 void* p_aligned_realloc ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_aligned_malloc (int,int) ; 
 int /*<<< orphan*/  test_aligned_offset_malloc (int,int,int) ; 
 int /*<<< orphan*/  test_aligned_offset_realloc (int,int,int,int) ; 
 int /*<<< orphan*/  test_aligned_realloc (int,int,int) ; 

__attribute__((used)) static void test_aligned(void)
{
    HMODULE msvcrt = GetModuleHandleA("msvcrt.dll");

    if (msvcrt == NULL)
        return;

    p_aligned_free = (void*)GetProcAddress(msvcrt, "_aligned_free");
    p_aligned_malloc = (void*)GetProcAddress(msvcrt, "_aligned_malloc");
    p_aligned_offset_malloc = (void*)GetProcAddress(msvcrt, "_aligned_offset_malloc");
    p_aligned_realloc = (void*)GetProcAddress(msvcrt, "_aligned_realloc");
    p_aligned_offset_realloc = (void*)GetProcAddress(msvcrt, "_aligned_offset_realloc");

    if (!p_aligned_free || !p_aligned_malloc || !p_aligned_offset_malloc || !p_aligned_realloc || !p_aligned_offset_realloc)
    {
        skip("aligned memory tests skipped\n");
        return;
    }

    test_aligned_malloc(256, 0);
    test_aligned_malloc(256, 1);
    test_aligned_malloc(256, 2);
    test_aligned_malloc(256, 3);
    test_aligned_malloc(256, 4);
    test_aligned_malloc(256, 8);
    test_aligned_malloc(256, 16);
    test_aligned_malloc(256, 32);
    test_aligned_malloc(256, 64);
    test_aligned_malloc(256, 127);
    test_aligned_malloc(256, 128);

    test_aligned_offset_malloc(256, 0, 0);
    test_aligned_offset_malloc(256, 1, 0);
    test_aligned_offset_malloc(256, 2, 0);
    test_aligned_offset_malloc(256, 3, 0);
    test_aligned_offset_malloc(256, 4, 0);
    test_aligned_offset_malloc(256, 8, 0);
    test_aligned_offset_malloc(256, 16, 0);
    test_aligned_offset_malloc(256, 32, 0);
    test_aligned_offset_malloc(256, 64, 0);
    test_aligned_offset_malloc(256, 127, 0);
    test_aligned_offset_malloc(256, 128, 0);

    test_aligned_offset_malloc(256, 0, 4);
    test_aligned_offset_malloc(256, 1, 4);
    test_aligned_offset_malloc(256, 2, 4);
    test_aligned_offset_malloc(256, 3, 4);
    test_aligned_offset_malloc(256, 4, 4);
    test_aligned_offset_malloc(256, 8, 4);
    test_aligned_offset_malloc(256, 16, 4);
    test_aligned_offset_malloc(256, 32, 4);
    test_aligned_offset_malloc(256, 64, 4);
    test_aligned_offset_malloc(256, 127, 4);
    test_aligned_offset_malloc(256, 128, 4);

    test_aligned_offset_malloc(256, 8, 7);
    test_aligned_offset_malloc(256, 8, 9);
    test_aligned_offset_malloc(256, 8, 16);
    test_aligned_offset_malloc(256, 8, 17);
    test_aligned_offset_malloc(256, 8, 254);
    test_aligned_offset_malloc(256, 8, 255);
    test_aligned_offset_malloc(256, 8, 256);
    test_aligned_offset_malloc(256, 8, 512);

    test_aligned_realloc(256, 512, 0);
    test_aligned_realloc(256, 128, 0);
    test_aligned_realloc(256, 512, 4);
    test_aligned_realloc(256, 128, 4);
    test_aligned_realloc(256, 512, 8);
    test_aligned_realloc(256, 128, 8);
    test_aligned_realloc(256, 512, 16);
    test_aligned_realloc(256, 128, 16);
    test_aligned_realloc(256, 512, 32);
    test_aligned_realloc(256, 128, 32);
    test_aligned_realloc(256, 512, 64);
    test_aligned_realloc(256, 128, 64);

    test_aligned_offset_realloc(256, 512, 0, 0);
    test_aligned_offset_realloc(256, 128, 0, 0);
    test_aligned_offset_realloc(256, 512, 4, 0);
    test_aligned_offset_realloc(256, 128, 4, 0);
    test_aligned_offset_realloc(256, 512, 8, 0);
    test_aligned_offset_realloc(256, 128, 8, 0);
    test_aligned_offset_realloc(256, 512, 16, 0);
    test_aligned_offset_realloc(256, 128, 16, 0);
    test_aligned_offset_realloc(256, 512, 32, 0);
    test_aligned_offset_realloc(256, 128, 32, 0);
    test_aligned_offset_realloc(256, 512, 64, 0);
    test_aligned_offset_realloc(256, 128, 64, 0);

    test_aligned_offset_realloc(256, 512, 0, 4);
    test_aligned_offset_realloc(256, 128, 0, 4);
    test_aligned_offset_realloc(256, 512, 4, 4);
    test_aligned_offset_realloc(256, 128, 4, 4);
    test_aligned_offset_realloc(256, 512, 8, 4);
    test_aligned_offset_realloc(256, 128, 8, 4);
    test_aligned_offset_realloc(256, 512, 16, 4);
    test_aligned_offset_realloc(256, 128, 16, 4);
    test_aligned_offset_realloc(256, 512, 32, 4);
    test_aligned_offset_realloc(256, 128, 32, 4);
    test_aligned_offset_realloc(256, 512, 64, 4);
    test_aligned_offset_realloc(256, 128, 64, 4);

    test_aligned_offset_realloc(256, 512, 0, 8);
    test_aligned_offset_realloc(256, 128, 0, 8);
    test_aligned_offset_realloc(256, 512, 4, 8);
    test_aligned_offset_realloc(256, 128, 4, 8);
    test_aligned_offset_realloc(256, 512, 8, 8);
    test_aligned_offset_realloc(256, 128, 8, 8);
    test_aligned_offset_realloc(256, 512, 16, 8);
    test_aligned_offset_realloc(256, 128, 16, 8);
    test_aligned_offset_realloc(256, 512, 32, 8);
    test_aligned_offset_realloc(256, 128, 32, 8);
    test_aligned_offset_realloc(256, 512, 64, 8);
    test_aligned_offset_realloc(256, 128, 64, 8);

    test_aligned_offset_realloc(256, 512, 0, 16);
    test_aligned_offset_realloc(256, 128, 0, 16);
    test_aligned_offset_realloc(256, 512, 4, 16);
    test_aligned_offset_realloc(256, 128, 4, 16);
    test_aligned_offset_realloc(256, 512, 8, 16);
    test_aligned_offset_realloc(256, 128, 8, 16);
    test_aligned_offset_realloc(256, 512, 16, 16);
    test_aligned_offset_realloc(256, 128, 16, 16);
    test_aligned_offset_realloc(256, 512, 32, 16);
    test_aligned_offset_realloc(256, 128, 32, 16);
    test_aligned_offset_realloc(256, 512, 64, 16);
    test_aligned_offset_realloc(256, 128, 64, 16);

    test_aligned_offset_realloc(256, 512, 0, 32);
    test_aligned_offset_realloc(256, 128, 0, 32);
    test_aligned_offset_realloc(256, 512, 4, 32);
    test_aligned_offset_realloc(256, 128, 4, 32);
    test_aligned_offset_realloc(256, 512, 8, 32);
    test_aligned_offset_realloc(256, 128, 8, 32);
    test_aligned_offset_realloc(256, 512, 16, 32);
    test_aligned_offset_realloc(256, 128, 16, 32);
    test_aligned_offset_realloc(256, 512, 32, 32);
    test_aligned_offset_realloc(256, 128, 32, 32);
    test_aligned_offset_realloc(256, 512, 64, 32);
    test_aligned_offset_realloc(256, 128, 64, 32);

    test_aligned_offset_realloc(256, 512, 0, 64);
    test_aligned_offset_realloc(256, 128, 0, 64);
    test_aligned_offset_realloc(256, 512, 4, 64);
    test_aligned_offset_realloc(256, 128, 4, 64);
    test_aligned_offset_realloc(256, 512, 8, 64);
    test_aligned_offset_realloc(256, 128, 8, 64);
    test_aligned_offset_realloc(256, 512, 16, 64);
    test_aligned_offset_realloc(256, 128, 16, 64);
    test_aligned_offset_realloc(256, 512, 32, 64);
    test_aligned_offset_realloc(256, 128, 32, 64);
    test_aligned_offset_realloc(256, 512, 64, 64);
    test_aligned_offset_realloc(256, 128, 64, 64);

    test_aligned_offset_realloc(256, 512, 0, 96);
    test_aligned_offset_realloc(256, 128, 0, 96);
    test_aligned_offset_realloc(256, 512, 4, 96);
    test_aligned_offset_realloc(256, 128, 4, 96);
    test_aligned_offset_realloc(256, 512, 8, 96);
    test_aligned_offset_realloc(256, 128, 8, 96);
    test_aligned_offset_realloc(256, 512, 16, 96);
    test_aligned_offset_realloc(256, 128, 16, 96);
    test_aligned_offset_realloc(256, 512, 32, 96);
    test_aligned_offset_realloc(256, 128, 32, 96);
    test_aligned_offset_realloc(256, 512, 64, 96);
    test_aligned_offset_realloc(256, 128, 64, 96);

    test_aligned_offset_realloc(256, 512, 0, 112);
    test_aligned_offset_realloc(256, 128, 0, 112);
    test_aligned_offset_realloc(256, 512, 4, 112);
    test_aligned_offset_realloc(256, 128, 4, 112);
    test_aligned_offset_realloc(256, 512, 8, 112);
    test_aligned_offset_realloc(256, 128, 8, 112);
    test_aligned_offset_realloc(256, 512, 16, 112);
    test_aligned_offset_realloc(256, 128, 16, 112);
    test_aligned_offset_realloc(256, 512, 32, 112);
    test_aligned_offset_realloc(256, 128, 32, 112);
    test_aligned_offset_realloc(256, 512, 64, 112);
    test_aligned_offset_realloc(256, 128, 64, 112);
}