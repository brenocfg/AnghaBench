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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FC_END ; 
 int /*<<< orphan*/  FC_PAD ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_end(FILE *file, unsigned int *tfsoff)
{
    if (*tfsoff % 2 == 0)
    {
        print_file(file, 2, "0x%x,\t/* FC_PAD */\n", FC_PAD);
        *tfsoff += 1;
    }
    print_file(file, 2, "0x%x,\t/* FC_END */\n", FC_END);
    *tfsoff += 1;
}