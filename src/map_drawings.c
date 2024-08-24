#include "cub3d.h"

void draw_player(t_game *game) 
{
    int player_x;
    int player_y;
    
    player_x = (int)(game->player->x_pos * game->x_scale);      // Scaling factors to fit the player within the minimap based on the window size
    player_y = (int)(game->player->y_pos * game->y_scale);
    printf(YELLOW"SCALED position: Player x: %d, Player y: %d\n"RESET, player_x, player_y);
    //Draw 3x3 square player
    if (player_x >= 0 && player_x < WIDTH && player_y >= 0 && player_y < HEIGHT)
        draw_square(game, player_x, player_y);
}

static void scale_and_draw_ray(t_game *game, double x, double y)
{
    double x_window;
    double y_window;

    x_window = x * game->x_scale;
    y_window = y * game->y_scale;
    if (x_window < WIDTH && x_window > 0 && y_window < HEIGHT && y_window > 0)
        mlx_put_pixel(game->img, x_window, y_window, PLUM);
}

//Minimap purposes, just to draw the pov from the player in a straight line
//It marks the direction the player is looking at based on the angle
int draw_pov(t_game *game, double angle, int iteration)
{
    double i;
    double x1;
    double y1;

    i = 0;
    x1 = game->player->x_pos + VISION_LENGTH * cos(angle); //cos(game->player->angle);
    y1 = game->player->y_pos + VISION_LENGTH * sin(angle);//sin(game->player->angle);

    // Loop through the line length and put each pixel
    while (i < VISION_LENGTH)                           //<----Refactor this one
    {
        double x;
        double y;
        /** CHANGE THIS **/
        /** THIS IS THE ALGORITHM, IT BRUTE FORCES THE CALCULATION OF THE WALL */
        x = (double)(game->player->x_pos + i * (x1 - game->player->x_pos) / VISION_LENGTH);
        y = (double)(game->player->y_pos + i * (y1 - game->player->y_pos) / VISION_LENGTH);
         
        /** PUT THIS ON TO SEE THE MADNESS OF ALL CALCULATIONS */
        //printf(BLUE"RAY OG: x: %f, y: %f\n"RESET, x, y);
        
        if (game->map[(int)y][(int)x] == 1) 
        {
            double delta_x = x - game->player->x_pos;     //<--- Testing purposes
            double delta_y = y - game->player->y_pos;
            double decimal_x = x - round(x);
            double decimal_y = y - round(y);
            printf(RED"DECIMAL X: %f, DECIMAL Y: %f\n"RESET, decimal_x, decimal_y);
            double minimum = min(fabs(decimal_x), fabs(decimal_y));
            printf(RED"MINIMUM: %f\n"RESET, minimum);
            if (minimum == fabs(decimal_x) && decimal_x > 0)                   // Touching X axis and facing East
                draw_obstacle(game, iteration, delta_x, delta_y, minimum, X_WALL);
            else if (minimum == fabs(decimal_x) && decimal_x < 0)            // Touching X axis and facing West (negative X)
                draw_obstacle(game, iteration, delta_x, delta_y, decimal_x, X_WALL);
            else if (minimum == fabs(decimal_y) && decimal_y > 0)              // Touching Y axis and facing South
                draw_obstacle(game, iteration, delta_x, delta_y, minimum, Y_WALL);
            else if (minimum == fabs(decimal_y) && decimal_y < 0)              // Touching Y axis
                draw_obstacle(game, iteration, delta_x, delta_y, decimal_y, Y_WALL);
            return (TRUE);
        }

        scale_and_draw_ray(game, x, y);     //<-- This is still for the map

        /** RATE AT WHICH WE CHANGE THE CALCULATIONS **/
        i += 0.01;
    }
    return (FALSE);
}

//Draw cone function with draw_pov but in a cone of 60 
void draw_cone(t_game *game) {
    
    double angle_step;
    double start_angle;
    double current_angle;
    int i;
    // Calculate the step angle between each ray
    angle_step = FOV_ANGLE / NUM_RAYS;                      //<--- Right now it is a proportion, maybe we should do fixed
    // Start angle (player's angle minus half the FOV)
    start_angle = game->player->angle - FOV_ANGLE / 2.0;
    i = 0;
    while (i < NUM_RAYS)
    {
        current_angle = start_angle + i * angle_step;
        draw_pov(game, current_angle, i);
        i++;
    }

}

void ft_draw(t_game *game)
{
    fill_background(game);
    fill_background_3d(game);
    draw_player(game);
    draw_cone(game);
    //draw_pov(game, game->player->angle, 1);                   //<------ For testing purposes, it tests a straight line
    mlx_image_to_window(game->mlx, game->img, 0, 0); 
}

