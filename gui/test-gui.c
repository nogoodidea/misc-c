#define NK_IMPLEMENTATION
#include "nuklear.h"

struct nk_context ctx;
nk_init_fixed(ctx, calloc(1, MAX_MEMORY), MAX_MEMORY, font);
nk_begin(ctx, "Show", nk_rect(50, 50, 220, 220),NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE);
nk_end(ctx);
