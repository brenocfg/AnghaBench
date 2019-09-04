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
struct sltg_typelib {int dummy; } ;
typedef  int /*<<< orphan*/  dummy ;

/* Variables and functions */
 int /*<<< orphan*/  chat (char*) ; 
 int /*<<< orphan*/  put_data (char const*,int) ; 

__attribute__((used)) static void sltg_write_helpstrings(struct sltg_typelib *typelib)
{
    static const char dummy[6];

    chat("sltg_write_helpstrings: writing dummy 6 bytes\n");

    put_data(dummy, sizeof(dummy));
}