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
typedef  int uint32_t ;
struct index {char c; int color; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ SDL_Surface ;

/* Variables and functions */
 int /*<<< orphan*/  LOGE (char*) ; 
 TYPE_1__* SDL_CreateRGBSurfaceFrom (int*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SDL_PREALLOC ; 
 int /*<<< orphan*/  SDL_assert (int) ; 
 int* SDL_malloc (int) ; 
 int find_color (struct index*,int,char,int*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int strtol (char const*,char**,int) ; 

SDL_Surface *
read_xpm(char *xpm[]) {
#if SDL_ASSERT_LEVEL >= 2
    // patch the XPM to change the icon color in debug mode
    xpm[2] = ".	c #CC00CC";
#endif

    char *endptr;
    // *** No error handling, assume the XPM source is valid ***
    // (it's in our source repo)
    // Assertions are only checked in debug
    int width = strtol(xpm[0], &endptr, 10);
    int height = strtol(endptr + 1, &endptr, 10);
    int colors = strtol(endptr + 1, &endptr, 10);
    int chars = strtol(endptr + 1, &endptr, 10);

    // sanity checks
    SDL_assert(0 <= width && width < 256);
    SDL_assert(0 <= height && height < 256);
    SDL_assert(0 <= colors && colors < 256);
    SDL_assert(chars == 1); // this implementation does not support more

    // init index
    struct index index[colors];
    for (int i = 0; i < colors; ++i) {
        const char *line = xpm[1+i];
        index[i].c = line[0];
        SDL_assert(line[1] == '\t');
        SDL_assert(line[2] == 'c');
        SDL_assert(line[3] == ' ');
        if (line[4] == '#') {
            index[i].color = 0xff000000 | strtol(&line[5], &endptr, 0x10);
            SDL_assert(*endptr == '\0');
        } else {
            SDL_assert(!strcmp("None", &line[4]));
            index[i].color = 0;
        }
    }

    // parse image
    uint32_t *pixels = SDL_malloc(4 * width * height);
    if (!pixels) {
        LOGE("Could not allocate icon memory");
        return NULL;
    }
    for (int y = 0; y < height; ++y) {
        const char *line = xpm[1 + colors + y];
        for (int x = 0; x < width; ++x) {
            char c = line[x];
            uint32_t color;
            bool color_found = find_color(index, colors, c, &color);
            SDL_assert(color_found);
            pixels[y * width + x] = color;
        }
    }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    uint32_t amask = 0x000000ff;
    uint32_t rmask = 0x0000ff00;
    uint32_t gmask = 0x00ff0000;
    uint32_t bmask = 0xff000000;
#else // little endian, like x86
    uint32_t amask = 0xff000000;
    uint32_t rmask = 0x00ff0000;
    uint32_t gmask = 0x0000ff00;
    uint32_t bmask = 0x000000ff;
#endif

    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(pixels,
                                                    width, height,
                                                    32, 4 * width,
                                                    rmask, gmask, bmask, amask);
    if (!surface) {
        LOGE("Could not create icon surface");
        return NULL;
    }
    // make the surface own the raw pixels
    surface->flags &= ~SDL_PREALLOC;
    return surface;
}