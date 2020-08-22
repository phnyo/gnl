/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 21:21:18 by fsugimot          #+#    #+#             */
/*   Updated: 2020/08/22 13:48:38 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strlen(char *line)
{
    int index;

    index = 0;
    while (line[index])
        index++;
    return (index);
}

int is_parsable(char *line, int ind)
{
    int index;

    index = ind - BUFFER_SIZE;
    if (index < 0)
        index = 0;
    while (line[index] && line[index] != '\n' && index < ind)
        index++;
    return (index != ind);
}

char    *add_memback(char *line, int size)
{
    char    *ret;
    int     alloc_size;
    int     index;

    index = 0;
    alloc_size = ft_strlen(line) + size;
    ret = malloc(alloc_size + 1);
    if (ret)
    {
        ret[alloc_size] = 0;
       while (index < alloc_size - size)
       {
           ret[index] = line[index];
           ++index;
       }
    }
    free(line); 
    return (ret);
}

int fetch_line(int fd, char **line, int ini_i)
{
    int index;
    int ret_num;
    char    *tmp;

    if (!line)
    {
        line = malloc(sizeof(char *));
        if (!line)
            return (0);
    }
    index = ini_i;
    if (!line[0])
    {
        tmp = malloc(sizeof(char));
        if (!tmp)
            return (-1);
        tmp[0] = 0;
    }
    else
        tmp = line[0];
    while (!tmp[0] || (tmp[0] == '\n' && !tmp[1]) || !is_parsable(tmp, index))
    {
        tmp = add_memback(tmp, BUFFER_SIZE);
        ret_num = read(fd, tmp + index, BUFFER_SIZE);
        if (ret_num <= 0)
            break;
        index += ret_num;
    }
    tmp[index] = 0;
    line[0] = tmp;
    return (index - ini_i);
}

char    *cut_back(char *line, int front, int back)
{
    char    *ret;
    int     itr;

    itr = back - front;
    ret = malloc(itr + 1);
    if (ret)
    {
        while (itr)
        {
            ret[itr - 1] = line[itr + front];
            itr--;
        }
    }
    free(line);
    return (ret);
}

void    cut_front(char *src, char **dst, int back)
{
    char    *ret;
    int     itr;

    free(dst[0]);
    itr = back;
    ret = malloc(itr + 1);
    if (ret)
    {
        ret[itr--] = 0;
        while (itr > -1)
        {
            ret[itr] = src[itr];
            itr--;
        }
    }
    dst[0] = ret;
}

int    cut_line(char **src, char **dst, int reari)
{
    int fronti;
    int ret;

    fronti = 0; 
    while (src[0][fronti] && src[0][fronti] != '\n')
        fronti++;
    ret = (src[0][fronti] ? 0 : 1);
    cut_front(src[0], dst, fronti);
    src[0] = cut_back(src[0], fronti, reari);
    return (ret);
}

int get_next_line(int fd, char **line)
{
    static char     **store;
    int             ret;
    int             is_eof;
    
    if (fd < 0 || !line)
        return (-1);
    if (!line[0])
        line[0] = malloc(sizeof(char));
    if (!store)
    {
        store = malloc(sizeof(char *));
        store[0] = 0;
    }
    if (!store || !line[0])
    {
        !store ? free(line[0]) : free(store);
        return (-1);
    }
    line[0][0] = 0;
    ret = fetch_line(fd, store, (store[0] ? ft_strlen(store[0]) : 0));
    if (!store)
        return (-1);
    is_eof = cut_line(store, line, ft_strlen(store[0]));
    if (!store)
        return (-1);
    if (!ret && is_eof)
    {
        free(store[0]);
        free(store);
        store = 0;
    }
    return (ret || store);
}
