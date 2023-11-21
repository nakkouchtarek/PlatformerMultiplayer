#include <global.h>
#include <stdio.h>
#include <player.h>
#include <mouvement.h>

void advance_level()
{
	if(level<=LEVEL_CAP)
	{
		reset_player_vel(&player);
		reset_player_vel(&player2);
		memset(map, 0, sizeof(*map));
		memset(targets, 0, sizeof(*targets));
		memset(blocks, 0, sizeof(*blocks));
		level++;
		count--;
		score=0;
		built=false;
	}
}

void downgrade_level()
{
	if(level>0)
	{
		reset_player_vel(&player);
		reset_player_vel(&player2);
		memset(map, 0, sizeof(*map));
		memset(targets, 0, sizeof(*targets));
		memset(blocks, 0, sizeof(*blocks));
		level--;
		count--;
		score=0;
		built=false;
	}
}

void reset_level()
{
	reset_player_vel(&player);
	reset_player_vel(&player2);
	memset(map, 0, sizeof(*map));
	memset(targets, 0, sizeof(*targets));
	memset(blocks, 0, sizeof(*blocks));
	score=0;
	count--;
	built=false;
}

void change_level()
{
    int index = 6;

	for(short i=0;i<5;i++)
	{
		level_phrase[6+i] = 0;
	}

    char str[10] = {0};
	char str2[10] = {0};
    
    sprintf(str, "%d", level); // 1
	sprintf(str2, "%d", LEVEL_CAP); // 10

	// Add level to our first string
    for(short i=0;i<strlen(str);i++)
    {
        level_phrase[index+i]=str[i];
    }

	level_phrase[index+strlen(str)] = '/';
	index+=strlen(str)+1;

	for(short i=0;i<strlen(str2);i++)
	{
		level_phrase[index+i] = str2[i];
	}
}