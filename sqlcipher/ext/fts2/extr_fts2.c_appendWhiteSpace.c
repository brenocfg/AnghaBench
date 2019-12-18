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
typedef  int /*<<< orphan*/  StringBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  endsInWhiteSpace (int /*<<< orphan*/ *) ; 
 scalar_t__ stringBufferLength (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void appendWhiteSpace(StringBuffer *p){
  if( stringBufferLength(p)==0 ) return;
  if( !endsInWhiteSpace(p) ) append(p, " ");
}