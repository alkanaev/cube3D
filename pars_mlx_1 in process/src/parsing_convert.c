#include "../cub3d.h"

int		len_mod(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '.')
		i++;
	while (str[i])
	{
		i++;
		j++;
	}
	return (j);
}

int		rosol_converting(const char *str, t_map *map)
{
	int signe;
	int sum;

	sum = 0;
	signe = 1;
	while (str[map->el] == ' ' || str[map->el] == '\t'
			|| str[map->el] == ',' || str[map->el] == '\n'
			|| str[map->el] == '\r' || str[map->el] == '\v'
			|| str[map->el] == '\f')
		map->el++;
	if (str[map->el] == '-' || str[map->el] == '+')
	{
		if (str[map->el] == '-')
			signe = -1;
		map->el++;
	}
	while (str[map->el] >= '0' && str[map->el] <= '9')
	{
		sum = (sum * 10) + (str[map->el] - 48);
		map->el++;
	}
	return (sum * signe);
}

int			check_colours_range_c(t_map *map)
{
	if (map->red_c < 0 || map->green_c < 0 || map->blue_c < 0
		|| map->red_c > 255 || map->green_c > 255 || map->blue_c > 255)
		return (0);
	else
		return (1);
}
int			check_colours_range_f(t_map *map)
{
	if (map->red_f < 0 || map->green_f < 0 || map->blue_f < 0
		|| map->red_f > 255 || map->green_f > 255 || map->blue_f > 255)
		return (0);
	else
		return (1);
}

char		**take_f_c_line(char *prep_line)
{
	int		i;
	int		len;
	char	**colours_line;

	i = 0;
	len = ft_strlen(prep_line);
	while (prep_line[i] != ' ')
		i++;
	colours_line = (char **)malloc(sizeof(char *) * 3);
	if (!colours_line)
		return (NULL);
	colours_line[0] = ft_substr(prep_line, 0, i);
	colours_line[1] = ft_substr(prep_line, i, len);
	colours_line[2] = NULL;
	return (colours_line);
}

char		**get_colours_codes(char *colours_line)
{
	int		i;
	char	**colours;
	int		separator;

	i = 0;
	separator = 0;
	colours = (char **)malloc(sizeof(char *) * 1);
	if (!colours)
		return (NULL);
	colours[0] = NULL;
	while (colours_line[i])
	{
		if (colours_line[i] == ',')
			separator++;
		i++;
	}
	if (separator == 2)
	{
		free(colours);
		colours = ft_split(colours_line, ',');
	}
	return (colours);
}

int	convert_colours(int r, int g, int b)
{
	int res;

	res = r;
	res = (res << 8) | g;
	res = (res << 8) | b;
	return (res);
}

int		f_converting(char *str, t_map *map)
{
	char	*prep_line;
	char	**colours_line;
	char	**colours;
	int		res;

	prep_line = ft_strtrim(str, SPACES);
	colours_line = take_f_c_line(prep_line);
	prep_line = ft_strtrim(colours_line[1], SPACES);
	if (!(prep_line))
		ft_putstr("map failed");
	res = 1;
	colours = get_colours_codes(prep_line);
	if (colours[0] == NULL && linelen(colours) != 3)
	{
		feedback(str, " -  Mistake in map codes (amount) \n");
		return (0);
	}
	else if (!ft_isnumber(colours[0]) || !ft_isnumber(colours[1])
			|| !ft_isnumber(colours[2]))
	{
		feedback(str, " -  Mistake in map codes (not num) \n");
		return (0);
	}
	else
	{
		map->red_f = atoi(colours[0]);
		map->green_f = atoi(colours[1]);
		map->blue_f = atoi(colours[2]);
		res = check_colours_range_f(map);

		if (res == 0)
			feedback(str, " - at least one of values not in a right range\n");
			return (0);
	}

	return (res);
}

int		c_converting(char *str, t_map *map)
{
	char	*prep_line;
	char	**colours_line;
	char	**colours;
	int		res;

	prep_line = ft_strtrim(str, SPACES);
	colours_line = take_f_c_line(prep_line);
	prep_line = ft_strtrim(colours_line[1], SPACES);
	if (!(prep_line))
		ft_putstr("map failed");
	res = 1;
	colours = get_colours_codes(prep_line);
	if (colours[0] == NULL && linelen(colours) != 3)
	{
		feedback(str, " -  Mistake in map codes (amount) \n");
		return (0);
	}
	else if (!ft_isnumber(colours[0]) || !ft_isnumber(colours[1])
			|| !ft_isnumber(colours[2]))
	{
		feedback(str, " -  Mistake in map codes (not num) \n");
		return (0);
	}
	else
	{
		map->red_c = atoi(colours[0]);
		map->green_c = atoi(colours[1]);
		map->blue_c = atoi(colours[2]);
		res = check_colours_range_c(map);

		if (res == 0)
			feedback(str, " - at least one of values not in a right range\n");
			return (0);
	}

	return (res);
}

