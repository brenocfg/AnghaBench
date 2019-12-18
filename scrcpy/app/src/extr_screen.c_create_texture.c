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
struct size {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  SDL_Texture ;
typedef  int /*<<< orphan*/  SDL_Renderer ;

/* Variables and functions */
 int /*<<< orphan*/ * SDL_CreateTexture (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_PIXELFORMAT_YV12 ; 
 int /*<<< orphan*/  SDL_TEXTUREACCESS_STREAMING ; 

__attribute__((used)) static inline SDL_Texture *
create_texture(SDL_Renderer *renderer, struct size frame_size) {
    return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12,
                             SDL_TEXTUREACCESS_STREAMING,
                             frame_size.width, frame_size.height);
}