/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:07:43 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/17 23:06:47 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_realpath.h"

size_t	count_up_moves(char *cmd)
{
	size_t		up_moves;
	size_t	i;

	up_moves = 0;
	i = 0;
	if (!cmd)
		return (0);
	while (cmd && cmd[i] && cmd[i + 1])
	{
		if (cmd[i] == '.' && cmd[i + 1] == '.')
			up_moves++;
		i++;
	}
	return (up_moves);
}

//size_t	count_moves_to_root(char *cmd)
//{
//	size_t		moves;
//	size_t	i;
//
//	moves = 0;
//	i = 0;
//	if (!cmd)
//		return (0);
//	while (cmd[i])
//	{
//		if (cmd[i] == '/')
//			moves++;
//		i++;
//	}
//	return (moves);
//}

/*
 * size_t	count_future_path_len(char *current_path, int up_moves)
{
	size_t	i;
	int		slash_seen;
	int		total_slash;

	i = 0;
	slash_seen = 0;
	total_slash = 0;
	while (current_path[i])
	{
		if (current_path[i] == '/')
			total_slash++;
		i++;
	}
	i = 0;
	while (current_path[i] && slash_seen <= total_slash - up_moves)
	{
		if (current_path[i] == '/')
			slash_seen++;
		i++;
	}
	i++;
	return (i);
}
 */

/*
 * static void	remove_one_dir_from_path(char path[4096])
{
	size_t	path_len;
	size_t	i;

	path_len = ft_strlen(path);
	if (path_len < 3)
	{
		ft_strlcpy(path, "/", 2);
		return ;
	}
	i = path_len - 2;
	while (path[i] != '/' && i > 0)
		i--;
	if (i == 0 || i > path_len)
		ft_strlcpy(path, "/", 2);
	else
	{
		while (path[i])
		{
			path[i] = '\0';
			i++;
		}
	}
}
 *
 */

/*static bool	begins_with_two_pts(const char *dir)
{
	size_t	i;

	i = 0;
	while (dir[i] && dir[i + 1])
	{
		if (dir[i] != '.' || dir[i + 1] != '/')
			break ;
		i += 2;
	}
	if (dir[i] && dir[i + 1] && (!dir[i + 2] || dir[i + 2] == '/'))
	{
		if (dir[i] == '.' && dir[i + 1] == '.')
			return (1);
	}
	return (0);
}*/

static bool	invalid_num_of_pts(char *dir)
{
	size_t	i;

	i = 0;
	if (!dir)
		return (0);
	if (!ft_strchr(dir, '.'))
		return (0);
	while (dir[i] && dir[i + 1] && dir[i + 2])
	{
		if (dir[i] == '.' && dir[i + 1] == '.' && dir[i + 2] == '.')
			return (1);
		i++;
	}
	//if (begins_with_two_pts(dir)) <-- me semble complètement inutile maintenant
	return (0);
	//return (1);
}

//static bool	next_dir_is_pts(const char *dir)
//{
//	if (dir[0] && dir[1])
//	{
//		if (dir[0] == '.' && dir[1] == '.' && (!dir[2] || dir[2] == '/'))
//			return (1);
//	}
//	return (0);
//}

//static size_t	count_up_moves(const char *dir, size_t i)
//{
//	size_t up_moves;
//
//	up_moves = 0;
//	if (next_dir_is_pts(dir + i))
//	{
//		up_moves++;
//		i += 2;
//	}
//	while (dir[i] && dir[i] == '/')
//	{
//		while (dir[i] && dir[i] == '/')
//			i++;
//		if (next_dir_is_pts(dir + i))
//		{
//			up_moves++;
//			i += 2;
//		}
//	}
//	return (up_moves);
//}

/*void	go_back_dir(const char *target, size_t *i, size_t *j)
{
	if ((*j) > 0)
	{
		(*j)--;
		while ((*j) > 0 && target[(*j) - 1] != '/')
			(*j)--;
	}
	(*i) += 2;
}

void put_final_slash(char *target, size_t *j)
{
	size_t i;

	dprintf(2, "target BEFORE final slash = %s\n", target);
	if (!target[(*j)] || *j == 0 || target[(*j) - 1] != '/')
	{
		target[*j] = '/';
		(*j)++;
	}
	i = *j;
	while (target[i] && i < PATH_MAX)
	{
		target[i] = '\0';
		i++;
	}
	++(*j);
	dprintf(2, "target after final slash = %s\n", target);
//	target[*j] = '/';
//	target[*j] = '\0';
}*/

/*void sanitize_path(char path[PATH_MAX], size_t end)
{
	size_t	i;
	size_t	j;
	char tmp[4096];

	i = 0;
	j = 0;
//	clear_path_char(tmp);
	dprintf(2, "tmp = %s\n", tmp);
	dprintf(2, "path = %s\n", path);
	ft_memset(path + end, 0, PATH_MAX - end);
//	path[end] = '\0';
	while (path[i])
	{
		if (path[i] == '/' && path[i + 1] && path[i + 1] == '/')
			i++;
		else
		{
			tmp[j] = path[i];
			dprintf(2, "tmp = %s\n", tmp);
			i++;
			j++;
		}
	}
	tmp[j] = 0;//'\0';
	dprintf(2, "tmp = %s\n", tmp);
	ft_strlcpy(path, tmp, j + 1);
}*/

void	remove_node_from_list(t_dir_list *node)
{
	t_dir_list	*prev;
	t_dir_list	*next;

	if (!node)
		return ;
	prev = node->prev;
	next = node->next;
	if (prev)
		prev->next = next;
	else if (next)
		next->prev = NULL;
	if (next)
		next->prev = prev;
	else if (prev)
		prev->next = NULL;
	free_safely_str(&node->subdir);
	free(node);
	node = NULL;
}

void remove_dirs_from_list(t_dir_list **list)
{
	t_dir_list	*tmp;
	t_dir_list	*start;

	tmp = *list;
	printf("tmp->subdir = %s\n", tmp->subdir);
	while (tmp && ft_strncmp(tmp->subdir, "..", 3) == 0)
		remove_node_from_list(tmp);
	start = tmp;
	while (tmp)
	{
		if (tmp->next && ft_strncmp(tmp->next->subdir, "..", 3) == 0)
		{
			remove_node_from_list(tmp->next);
			remove_node_from_list(tmp);
			tmp = start;
		}
		else if (ft_strncmp(tmp->subdir, ".", 2) == 0
			|| ft_strncmp(tmp->subdir, "..", 3) == 0)
		{
			remove_node_from_list(tmp);
			tmp = start;
		}
		printf("tmp->subdir = %s\n", tmp->subdir);
		tmp = tmp->next;
	}
	tmp = NULL;
	*list = start;
	// À ENLEVER ÉVIDEMMENT
	while (start)
	{
		printf("start->subdir = %s\n", start->subdir);
		start = start->next;
	}
}

char	*join_sep_safely(char *s1, char *s2, char sep, bool free_s1)
{
	size_t	total_len;
	char	*dest;
	int		x;
	int		y;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!dest)
		return (NULL);
	x = -1;
	y = 0;
	while (s1[++x])
		dest[x] = (char)s1[x];
	dest[x++] = sep;
	while (s2[y])
		dest[x++] = (char)s2[y++];
	dest[x] = '\0';
	if (free_s1)
		free_safely_str(&s1);
	return (dest);
}

t_dir_list	*prepare_list(t_minishell *m, char *dir)
{
	t_dir_list	*list;
	char			*dir_cpy;

	dir_cpy = ft_strdup(dir);
	if (!dir_cpy)
		return (NULL);
	if (dir && dir[0] && dir[0] != '/')
	{
		free_safely_str(&dir_cpy);
		dir_cpy = join_sep_safely(m->current_path, dir, '/', 0);
		if (!dir)
			return (NULL);
	}
	list = ft_split_list(dir_cpy, '/');
	return (list);
}

char	*replace_pts_with_path(t_minishell	*m, char *dir)
{
	char	*path;
	t_dir_list	*list;
	t_dir_list *start;

	dprintf(2, "REPLACE IS COMING :D\n");
	list = prepare_list(m, dir);
	if (!list)
		return (NULL);
	list->prev = (t_dir_list *) malloc(sizeof (t_dir_list));
	if (list->prev == NULL)
	{
		ft_free_list(list);
		return (NULL);
	}
	list->prev->next = list;
	list = list->prev;
	list->subdir = ft_strdup("/");
	if (!list->subdir)
	{
		ft_free_list(list);
		return (NULL);
	}
	t_dir_list *print = list;
	while (print)
	{
		dprintf(2, "print->subdir = %s\n", print->subdir);
		print = print->next;
	}
	remove_dirs_from_list(&list);
	if (!list || !list->next)
		return (ft_strdup("/"));
	path = ft_strdup(list->subdir);
	if (!path)
	{
		ft_free_list(list);
		return (NULL);
	}
	start = list;
	list = list->next;
	while (list)
	{
		if (ft_strncmp(path, "/", 2) == 0)
			path = ft_strjoin(path, list->subdir);
		else
			path = join_sep_safely(path, list->subdir, '/', 1);
		if (!path)
		{
			ft_free_list(start);
			return (NULL);
		}
		dprintf(2, "THE FUCKING LIST = %s\n", list->subdir);
		dprintf(2, "THE FUCKING PATH = %s\n", path);
		list = list->next;
	}
	ft_free_list(list);
	dprintf(2, "FINAL PATH :D\n%s\n", path);
	return (path);
}

char	*ft_realpath(t_minishell *m, char *dir)
{
	if (ft_strncmp(dir, "/", 2) == 0)
		return (ft_strdup("/"));
	if ((dir && dir[0] == '/' && ft_strchr(dir, '.') == NULL)
		|| invalid_num_of_pts(dir))
		return (ft_strdup(dir));
	dprintf(2, "DIR = %s\n", dir);
	if (contains_only_charset(dir, "./")
		&& count_up_moves(m->current_path) < count_up_moves(dir))
		return (ft_strdup("/"));
	dprintf(2, "REPLACE IS COMING :D\nMoves up == %lu\nTO ROOT == %lu\n", count_up_moves(dir), count_up_moves(m->current_path));
	return (replace_pts_with_path(m, dir));
}
//	if ((dir_len <= PATH_MAX
//		&& ((ft_strchr(dir, '.') == NULL) || !ft_strncmp(dir, ".", 2))
//		&& (!dir[0] || !dir[1] || invalid_num_of_pts(dir))))
//	//	|| access(m->current_path, X_OK) == 0))
//		{
//			curpath_len = ft_strlen(m->current_path);
//			ft_strlcpy(tmp, m->current_path, curpath_len + 1);
//			ft_strlcat(tmp, "/", curpath_len + 2);
//			ft_strlcat(tmp, dir, curpath_len + 2 + dir_len);
//			//ft_strlcpy(target_path, tmp, ft_strlen(tmp) + 1);
//			return (ft_strdup(dir)); //  <-- Non sens mais juste parce que je veux pouvoir compiler pour infile/outfile
//		}
//		return (ft_strdup(dir)); //  <-- Non sens mais juste parce que je veux pouvoir compiler pour infile/outfile

	//replace_pts_with_path(, target_path, dir);
	//dprintf(2, "FINAL TARGET PATH :D\n%s\n", target_path);
//}
/* OLD REALPATH
 * void	ft_realpath(t_minishell *m, char *dir)
{
	size_t	dir_len;
	size_t	curpath_len;
	char tmp[PATH_MAX];

	clear_path_char(tmp);
	dir_len = ft_strlen(dir);
	ft_strlcpy(m->target_given, dir, dir_len + 1);
	if (ft_strncmp(dir, "/", 2) == 0)
	{
		ft_strlcpy(m->target_path, dir, 2);
		return ;
	}
	if (dir && dir[0] == '/')
		return ;
	if ((dir_len <= PATH_MAX
		 && ((ft_strchr(dir, '.') == NULL) || !ft_strncmp(dir, ".", 2))
		 && (!dir[0] || !dir[1] || invalid_num_of_pts(dir))))
		//	|| access(m->current_path, X_OK) == 0))
	{
		curpath_len = ft_strlen(m->current_path);
		ft_strlcpy(tmp, m->current_path, curpath_len + 1);
		ft_strlcat(tmp, "/", curpath_len + 2);
		ft_strlcat(tmp, dir, curpath_len + 2 + dir_len);
		ft_strlcpy(m->target_path, tmp, ft_strlen(tmp) + 1);
		sanitize_path(m->target_path, ft_strlen(m->target_path));
		return ;
	}
	replace_pts_with_path(m, m->target_path, dir);
	dprintf(2, "I BUG :D\n%s\n", m->target_path);
	sanitize_path(m->target_path, ft_strlen(m->target_path));
}*/
/*
a/b/c/d/e/f/g/h/i
a/b/c/../c/../../b/

a
b
NULL
*/
