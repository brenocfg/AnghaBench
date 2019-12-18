#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ stbfile ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (void*,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stb__fbackpatch(stbfile *f, unsigned int where, void *buffer, unsigned int len)
{
   fseek(f->f, where, SEEK_SET);
   fwrite(buffer, 1, len, f->f);
   fseek(f->f, 0, SEEK_END);
}