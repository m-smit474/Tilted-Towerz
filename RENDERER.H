#ifndef RENDERER_H
#define RENDERER_H
#include "types.h"
#include "model.h"

void render(const struct Model* model, UINT16* base);
void render_block(const struct Block *block, UINT16 *base);

#endif