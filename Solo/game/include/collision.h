#include <entity.h>
#include <global.h>

#include <SDL2/SDL.h>
#include <stdio.h>
#include <global.h>
#include <entity.h>
#include <player.h>

// Check if block collides with map
bool check_block_map_collision(Entity* block, Player* p);
void player_block_collision(Player* p);
void player_map_collision(Player* p);
void collision(Player* p);