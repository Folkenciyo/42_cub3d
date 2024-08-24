#ifndef DRAWINGS_H
# define DRAWINGS_H
# include "cub3d.h"

/* DRAWING UTILS */
void put_color(t_game *game, int x, int y);
void fill_background(t_game *game);
void draw_square(t_game *game, int player_x, int player_y) ;
double min(double a, double b);


/* MAIN DRAWINGS FUNCTIONS */
void fill_background(t_game *game);
void draw_player(t_game *game); // For testing purposes, position of the player
//Vision
int draw_pov(t_game *game, double angle, int iteration);
//void draw_cone(t_game *game, int length);
void draw_cone(t_game *game);

void ft_draw(t_game *game);

/* 3D WORLD DRAWINGS */
void fill_background_3d(t_game *game);
void draw_obstacle(t_game *game, int iteration, double delta_x, double delta_y, double min_decimal, int wall);


#endif 