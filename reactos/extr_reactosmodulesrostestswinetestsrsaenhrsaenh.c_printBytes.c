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
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void printBytes(const char *heading, const BYTE *pb, size_t cb)
{
    size_t i;
    printf("%s: ",heading);
    for(i=0;i<cb;i++)
        printf("0x%02x,",pb[i]);
    putchar('\n');
}