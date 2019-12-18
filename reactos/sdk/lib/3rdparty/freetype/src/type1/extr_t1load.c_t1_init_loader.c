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
typedef  int /*<<< orphan*/  T1_Loader ;
typedef  int /*<<< orphan*/  T1_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_ZERO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  t1_init_loader( T1_Loader  loader,
                  T1_Face    face )
  {
    FT_UNUSED( face );

    FT_ZERO( loader );
  }