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
typedef  int UINT ;
typedef  unsigned char* LPSTR ;
typedef  int* LPCSTR ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ HANKATA (unsigned char) ; 
 scalar_t__ SJIS1 (unsigned char) ; 
 scalar_t__ SJIS2 (unsigned char) ; 
 scalar_t__ TRUE ; 
 scalar_t__ enter_shift (unsigned char*,int) ; 
 scalar_t__ exit_shift (unsigned char*,int) ; 
 scalar_t__ han2zen (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  sjis2jis (unsigned char*,unsigned char*) ; 

__attribute__((used)) static UINT ConvertSJIS2JIS(LPCSTR input, DWORD count, LPSTR output)
{
    DWORD i = 0;
    int j = 0;
    unsigned char p2,p;
    BOOL shifted = FALSE;

    while (i < count)
    {
        p = input[i] & 0xff;
        if (p == 10 || p == 13) /* NL and CR */
        {
            if (shifted)
            {
                shifted = FALSE;
                j += exit_shift(output,j);
            }
            if (output)
                output[j++] = p;
            else
                j++;
        }
        else
        {
            if (SJIS1(p))
            {
                i++;
                if (i >= count)
                    return 0;
                p2 = input[i] & 0xff;
                if (SJIS2(p2))
                {
                    sjis2jis(&p,&p2);
                    if (!shifted)
                    {
                        shifted = TRUE;
                        j+=enter_shift(output,j);
                    }
                }

                if (output)
                {
                    output[j++]=p;
                    output[j++]=p2;
                }
                else
                    j+=2;
            }
            else
            {
                if (HANKATA(p))
                {
                    if ((i+1) >= count)
                        return 0;
                    p2 = input[i+1] & 0xff;
                    i+=han2zen(&p,&p2);
                    sjis2jis(&p,&p2);
                    if (!shifted)
                    {
                        shifted = TRUE;
                        j+=enter_shift(output,j);
                    }
                    if (output)
                    {
                        output[j++]=p;
                        output[j++]=p2;
                    }
                    else
                        j+=2;
                }
                else
                {
                    if (shifted)
                    {
                        shifted = FALSE;
                        j += exit_shift(output,j);
                    }
                    if (output)
                        output[j++]=p;
                    else
                        j++;
                }
            }
        }
        i++;
    }
    if (shifted)
        j += exit_shift(output,j);
    return j;
}