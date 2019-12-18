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
 scalar_t__ safe_isspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stringBufferData (int /*<<< orphan*/ *) ; 
 int stringBufferLength (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int endsInWhiteSpace(StringBuffer *p){
  return stringBufferLength(p)>0 &&
    safe_isspace(stringBufferData(p)[stringBufferLength(p)-1]);
}