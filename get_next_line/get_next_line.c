/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:55:17 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/02/22 14:55:18 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

size_t ft_strlen(char *str)
{
    size_t i;
    i = 0;
    while(str[i])
    {
        i++;
    }
    return i;
}

int ft_strchar(char *str)
{
    size_t i;
    i = 0;
    while(str[i])
    {
        if(str[i] == '\n')
            return 1;
        i++;
    }
    return 0;
}

char *ft_strdup(char *str)
{
    size_t i;
    size_t len;
    i = 0;
    len = ft_strlen(str);
    char *dst = malloc(sizeof(char ) * len + 1);
    if(!dst)
        return 0;
    while(str[i])
    {
        dst[i] = str[i];
        i++;
    }
    dst[i] = '\0';
    return dst;
}

char *ft_strjoin(char *str1,char *str2)
{
    size_t len = 0;
    size_t i = 0;
    len += ft_strlen(str2);
    len += ft_strlen(str1);
    char *dst = malloc(sizeof(char) * len + 1);
    if(!dst)
        return 0;
    while(str1[i])
    {
        dst[i] = str1[i];
        i++;
    }
    int j = 0;
    while(str2[j])
    {
        dst[i] = str2[j];
        i++;
        j++;
    }
    dst[i] = '\0';
    return dst;
}


char *ft_substr(char *str,int start,int len)
{
    int i = 0;
    if(!str)
        return 0;
    int slen = ft_strlen(str);
    if(slen < len)
        len = slen;
    char *dst = malloc(sizeof(char ) * len +1);
    if(!dst)
        return 0;
    while(i < len && start < slen)
    {
        dst[i] = str[start];
        i++;
        start++;
    }
    dst[i] = '\0';
    return dst;
}

char *ft_copy(int fd,char *buffer,char *backup)
{
    char *tmp;
    int read_line = 1;
    while(read_line != 0)
    {
        read_line = read(fd,buffer,BUFFER_SIZE);

        if(read_line <= 0)
            break;
        buffer[read_line] = '\0';
        if(!backup)
            backup = ft_strdup("");
        tmp = backup;
        backup = ft_strjoin(tmp,buffer);
        free(tmp);
        tmp = 0;
        if(ft_strchar(buffer) == 1)
            break;
    }
    return backup;
}

char *backup_extract(char *len)
{
    int i;
    i = 0;
    while(len[i] != '\n' && len[i] != '\0')
        i++;
    if(len[i] == 0 || len[1] == 0)
        return 0;
    char *backup = ft_substr(len,i+1,ft_strlen(len) - i);
    if(*backup)
    {
        free(backup);
        return 0;
    }
    len[i + 1] = '\0';
    return backup;
}

char *get_next_line(int fd)
{
    char *line;
    char *buffer;
    static char *backup;

    if(fd < 0 || BUFFER_SIZE <= 0)
        return 0;
    buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if(!buffer)
        return 0;
    line = ft_copy(fd,buffer,backup);
    free(buffer);
    buffer = 0;
    if(!line)
        return 0;
    backup = backup_extract(line);
    return line;
}