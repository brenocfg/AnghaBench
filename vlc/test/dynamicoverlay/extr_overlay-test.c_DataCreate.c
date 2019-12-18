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

/* Variables and functions */
 size_t HEIGHT ; 
 int /*<<< orphan*/  TEXT ; 
 int /*<<< orphan*/  TEXTSIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* p_imageRGBA ; 
 int /*<<< orphan*/  p_text ; 

void DataCreate( void ) {
    char *p_data = p_imageRGBA;
    for( size_t i = 0; i < HEIGHT; ++i ) {
        for( size_t j = 0; j < HEIGHT; ++j ) {
            *(p_data++) = i * 4 & 0xFF;
            *(p_data++) = 0xFF;
            *(p_data++) = 0x00;
            *(p_data++) = j * 4 & 0xFF;
        }
    }

    memcpy( p_text, TEXT, TEXTSIZE );
}