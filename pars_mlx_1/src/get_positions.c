#include "../cub3d.h"

void get_player_position(t_all *all)
{
    size_t  max_y = all->map.max_columns + 1;
    //printf("%d\n", max_y);
    size_t  y = 0;
    size_t  x;
    while (y < max_y)
    {
        x = 0;
        size_t  max_x = ft_strlen(all->map.map[y]);
        while (x < max_x)
        {
        //    printf("%c ", all->map.map[i][j]);
            if (all->map.map[y][x] == 'N' || all->map.map[y][x] == 'S' || all->map.map[y][x] == 'E' || all->map.map[y][x] == 'W')
	        {
		        all->player.x = x * SCALE + 32;
		        all->player.y = y * SCALE + 32;
		        //printf("%f\n", all->player.x);
		        //printf("%f\n", all->player.y);
	        }
            if (all->map.map[y][x] == '2')
                all->sprite_count++;
            x++;     
        }
        y++;
    }
}

void get_sprite_positions(t_all *all)
{
    int i = 0;
    size_t  max_y = all->map.max_columns + 1;
    //printf("%d\n", max_y);
    size_t  y = 0;
    size_t  x;
    while (i < all->sprite_count)
    {
        while (y < max_y)
        {
            x = 0;
            size_t  max_x = ft_strlen(all->map.map[y]);
            while (x < max_x)
            {
                if (all->map.map[y][x] == '2')
                {
                    all->sprite[i].x = x * SCALE + 32;
                    all->sprite[i].y = y * SCALE + 32;
                    i++;
                }
            }
            x++;     
        }
        y++;
    }
}