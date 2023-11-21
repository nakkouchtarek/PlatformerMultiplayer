#include <global.h>
#include <stdio.h>

int last_block_x;
int last_block_y;
int block_count_r=0;

void change_step()
{
    int index = 6;

    char str[10] = {0};
    
    sprintf(str, "%d", count);

	// Add level to our first string
    for(short i=0;i<strlen(str);i++)
    {
        step_count[index]=str[i];
		index++;
    }
}


void keep_step_count()
{
	if(player.p.dst.x/32 != last_val_x || player.p.dst.y/32 != last_val_y)
	{
		count++;
		change_step();	
	}
	
	last_val_x=player.p.dst.x/32;
	last_val_y=player.p.dst.y/32;
}

void change_bc()
{
    int index = 5;

    char str[10] = {0};
    
    sprintf(str, "%d", block_count_r);

	// Add level to our first string
    for(short i=0;i<strlen(str);i++)
    {
        count_phrase[index]=str[i];
		index++;
    }
}

void keep_block_count()
{
	if(player.block_index!=-1)
	{
		if(blocks[player.block_index].dst.x/32 != last_block_x || blocks[player.block_index].dst.y/32 != last_block_y)
		{
			block_count_r++;
			change_bc();
		}

		last_block_x=(int)(blocks[player.block_index].dst.x/32);
		last_block_y=(int)(blocks[player.block_index].dst.y/32);

	}
	
}