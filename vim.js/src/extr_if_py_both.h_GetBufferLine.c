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
typedef  int /*<<< orphan*/  linenr_T ;
typedef  int /*<<< orphan*/  buf_T ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  scalar_t__ PyInt ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * LineToString (char*) ; 
 scalar_t__ ml_get_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
GetBufferLine(buf_T *buf, PyInt n)
{
    return LineToString((char *)ml_get_buf(buf, (linenr_T)n, FALSE));
}