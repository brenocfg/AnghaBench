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
typedef  enum optdec { ____Placeholder_optdec } optdec ;
typedef  enum optcla { ____Placeholder_optcla } optcla ;

/* Variables and functions */
 int const avx ; 
 int const dreidnowext ; 
 int const dreidnowext_vintage ; 
 int const mmx ; 
 int mmxsse ; 
 int const neon ; 
 int const neon64 ; 
 int normal ; 
 int const sse ; 
 int const sse_vintage ; 
 int const x86_64 ; 

enum optcla decclass(const enum optdec type)
{
	return
	(
		   type == mmx
		|| type == sse
		|| type == sse_vintage
		|| type == dreidnowext
		|| type == dreidnowext_vintage
		|| type == x86_64
		|| type == neon
		|| type == neon64
		|| type == avx
	) ? mmxsse : normal;
}