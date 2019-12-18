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
typedef  int /*<<< orphan*/  stbi ;
struct TYPE_3__ {int /*<<< orphan*/ * s; } ;
typedef  TYPE_1__ jpeg ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_type ; 
 int decode_jpeg_header (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbi_rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stbi_jpeg_test(stbi *s)
{
   int r;
   jpeg j;
   j.s = s;
   r = decode_jpeg_header(&j, SCAN_type);
   stbi_rewind(s);
   return r;
}