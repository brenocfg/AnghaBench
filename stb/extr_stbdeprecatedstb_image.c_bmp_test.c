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
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int /*<<< orphan*/  get16le (int /*<<< orphan*/ *) ; 
 int get32le (int /*<<< orphan*/ *) ; 
 char get8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bmp_test(stbi *s)
{
   int sz;
   if (get8(s) != 'B') return 0;
   if (get8(s) != 'M') return 0;
   get32le(s); // discard filesize
   get16le(s); // discard reserved
   get16le(s); // discard reserved
   get32le(s); // discard data offset
   sz = get32le(s);
   if (sz == 12 || sz == 40 || sz == 56 || sz == 108) return 1;
   return 0;
}