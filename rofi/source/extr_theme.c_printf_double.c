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

/* Variables and functions */
 int G_ASCII_DTOSTR_BUF_SIZE ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_ascii_formatd (char*,int,char*,double) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) inline static void printf_double ( double d )
{
    char buf[G_ASCII_DTOSTR_BUF_SIZE];
    g_ascii_formatd ( buf, G_ASCII_DTOSTR_BUF_SIZE, "%.4lf", d );
    fputs ( buf, stdout );
}