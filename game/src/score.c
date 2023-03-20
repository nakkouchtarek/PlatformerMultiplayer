#include <global.h>
#include <stdio.h>
#include <methods.h>
#include <text.h>
#include <map.h>

void change_score()
{
    int index = 6;

    char str[10] = {0};
	char str2[10] = {0};
    
    sprintf(str, "%d", score);
	sprintf(str2, "%d", target_count);

	// Add level to our first string
    for(short i=0;i<strlen(score_phrase);i++)
    {
        if(str[i]==0)
            break;
        else
        {
            score_phrase[index+i]=str[i];
			index++;
        }
    }

	score_phrase[index] = '/';

	for(short i=0;i<strlen(str2);i++)
	{
		score_phrase[index+1+i] = str2[i];
	}

}

// detect if tnt on top of target
void detect_score()
{
	for(short i=0;i<target_count;i++)
		{
			for(short j=0;j<block_count;j++)
			{
				if(SDL_HasIntersection(&targets[i].rect,&blocks[j].dst) && targets[i].type == 'f')
				{
					score++;
					change_score();
					targets[i].type = 's';
				}
			}
		}
}

// see if tnt still on top of target
void detect_score_validity()
{
	for(short i=0;i<target_count;i++)
		{
			if(targets[i].type=='s')
			{
				c=0;
				for(short j=0;j<block_count;j++)
				{
					if(SDL_HasIntersection(&targets[i].rect,&blocks[j].dst))
						c++;
				}
				
				if(c==0)
				{
					targets[i].type='f';
					score--;
					change_score();
				}

				c=0;

			}
		}
}

void score_func()
{
	detect_score();
	// checks if box is still on target
	detect_score_validity();
}
