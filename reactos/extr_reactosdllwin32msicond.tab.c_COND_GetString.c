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
struct cond_str {int len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  COND_input ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__* cond_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LPWSTR COND_GetString( COND_input *cond, const struct cond_str *str )
{
    LPWSTR ret;

    ret = cond_alloc( cond, (str->len+1) * sizeof (WCHAR) );
    if( ret )
    {
        memcpy( ret, str->data, str->len * sizeof(WCHAR));
        ret[str->len]=0;
    }
    TRACE("Got identifier %s\n",debugstr_w(ret));
    return ret;
}