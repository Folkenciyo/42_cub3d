/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juguerre <juguerre@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:05:07 by juguerre          #+#    #+#             */
/*   Updated: 2024/09/03 00:05:07 by juguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "cub3d.h"

typedef struct s_txtr
{
	char			*key;
	char			*value;
	void			*img;
	int				width;
	int				height;
	struct s_txtr	*next;
}	t_txtr;

typedef struct s_init_data
{
	char	**map2d;
	char	**map2d_square;
	int		m_rows;
	int		m_cols;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		fd;
	int		counter;
	char	*line;
	char	*map;
	char	*tx2re;
	char	**texture;
	char	**floor;
	char	**ceiling;
	char	**rgb;
	t_txtr	*t;
}	t_init_data;

int		parsing(int argc, char **argv, t_init_data *data);
int		extensionChecker(char *file);
/* MAP PARSING */
int		read_map(char *file, t_init_data *data);
void	read_map_ext(t_init_data *data);
int		read_map_return_n_free(t_init_data *data);
int		map_validation(t_init_data *data);
int		largest_line(t_init_data *data);
int		map_size(char **map);
char	*fix_line(char *line, int maxlen);
int		h_map(char **map);
int		w_map(char **map);
void	get_rows_cols(t_init_data *data);
char	*get_map(t_init_data *data);
void	jorgito(char **line, int *flag);
int		is_invalid_char_or_comma(const char *line, int i);
/* APROVE MAP */
int		aprove_map(t_init_data *data);
int		check_texture_space(t_init_data *data);
int		check_texture_if_valid(char *line);
int		parse_rgb(char **texture);
int		count_vergules(char *rgb);
int		check_pos_ofv(char *line);
int		check_duplicate(t_init_data *data);
int		check_first_last_line(char **map);
char	*get_last_line(char **map);
int		surrounded_by_one(char **map);
/* TEXTURES PARSING */
int		check_color_texture(char *line);
int		check_texture_mount(t_init_data *data);
int		list_texture(t_init_data *data);
t_txtr	*new_texture(char *line);
int		get_index(char *line, int i);
void	list_back_texture(t_txtr **texture, t_txtr *new);
int		colors_texture(t_init_data *data);
void	ft_process_rgb_color(t_txtr *tmp, t_init_data *data);
int		check_color_value(char **rgb);
int		init_texture(t_init_data *data);
/* PLAYER */
void	get_player_position(t_init_data *data);
/* FREE DATA */
int		free_data(char *line, char *tx2re, int fd);
int		free_array2d(char **array);
void	free_map(t_init_data *data);
void	free_list(t_txtr *texture);

#endif 