#include "../ced/renderer.h"
#include "../map.h"
#include "../player.h"

void draw_map(CedRenderer* renderer, Map* map, float scale);
void draw_map_player(CedRenderer* renderer, Map* map, Player* p, float scale);