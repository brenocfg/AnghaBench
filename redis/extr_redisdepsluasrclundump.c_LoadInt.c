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
typedef  int /*<<< orphan*/  LoadState ;

/* Variables and functions */
 int /*<<< orphan*/  IF (int,char*) ; 
 int /*<<< orphan*/  LoadVar (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int LoadInt(LoadState* S)
{
 int x;
 LoadVar(S,x);
 IF (x<0, "bad integer");
 return x;
}