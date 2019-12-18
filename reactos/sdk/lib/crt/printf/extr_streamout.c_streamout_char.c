#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int _flag; int _cnt; scalar_t__ _ptr; int /*<<< orphan*/ * _base; } ;
typedef  int TCHAR ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int _IOSTRG ; 
 scalar_t__ _TEOF ; 
 scalar_t__ _fputtc (int,TYPE_1__*) ; 

__attribute__((used)) static
int
streamout_char(FILE *stream, int chr)
{
#if !defined(_USER32_WSPRINTF)
     if ((stream->_flag & _IOSTRG) && (stream->_base == NULL))
        return 1;
#endif
#if defined(_USER32_WSPRINTF) || defined(_LIBCNT_)
    /* Check if the buffer is full */
    if (stream->_cnt < sizeof(TCHAR))
        return 0;

    *(TCHAR*)stream->_ptr = chr;
    stream->_ptr += sizeof(TCHAR);
    stream->_cnt -= sizeof(TCHAR);

    return 1;
#else
    return _fputtc((TCHAR)chr, stream) != _TEOF;
#endif
}