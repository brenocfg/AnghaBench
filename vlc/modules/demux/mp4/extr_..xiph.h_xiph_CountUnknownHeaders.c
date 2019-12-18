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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;

/* Variables and functions */
 int xiph_CountHeaders (void const*,unsigned int) ; 
 int xiph_CountLavcHeaders (void const*,unsigned int) ; 
 scalar_t__ xiph_IsLavcFormat (void const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned xiph_CountUnknownHeaders(const void *p_extra, unsigned i_extra,
                                                vlc_fourcc_t i_codec)
{
    if (xiph_IsLavcFormat(p_extra, i_extra, i_codec))
        return xiph_CountLavcHeaders(p_extra, i_extra);
    else
        return xiph_CountHeaders(p_extra, i_extra);
}