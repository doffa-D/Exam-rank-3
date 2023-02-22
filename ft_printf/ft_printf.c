/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:55:14 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/02/22 14:55:14 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int ft_putchar(char c)
{
    write(1,&c,1);
    return 1;
}

int ft_putstr(char *str)
{
    int i;
    i = 0;
    if(!str)
    {
        write(1,"(null)",6);
        return 6;
    }
    while(str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
    return i;
}


int count(long int nbr,int base)
{
    int i;
    i = 0;
    if(nbr < 0)
    {
        i++;
        nbr *= -1;
    }
    if(nbr == 0)
        i++;
    while(nbr)
    {
        i++;
        nbr /= base;
    }
    return i;
}


int ft_putnbr(int nb)
{
    long int nbr = nb;
    int len = count(nbr,10);
    char a[] = "0123456789";
    if(nb < 0)
    {
        ft_putchar('-');
        nbr *= -1;
    }
    if(nbr >= 10)
    {
        ft_putnbr(nbr / 10);
        ft_putnbr(nbr % 10);
    }
    else
    {
        if(nbr <= 9)
        {
            ft_putchar(nbr + '0');
        }
        else
            ft_putchar(a[nbr % 10]);
    }
    return len;
}


int ft_putnbr_hex(unsigned int nb)
{
    int len = count(nb,16);
    long int nbr = nb;
    char a[] = "0123456789abcdef";
    if(nbr >= 16)
    {
        ft_putnbr_hex(nbr / 16);
        ft_putnbr_hex(nbr % 16);
    }
    else
    {
        if(nbr <= 9)
        {
            ft_putchar(nbr + '0');
        }
        else
            ft_putchar(a[nbr % 16]);
    }
    return len;
}

int ft_ptr(const char c,va_list ptr)
{
    if(c == 'd')
        return(ft_putnbr(va_arg(ptr,int)));
    else if(c == 'x')
        return(ft_putnbr_hex(va_arg(ptr,unsigned int)));
    else if(c == 's')
        return(ft_putstr(va_arg(ptr,char *)));
    else if(c == '%')
        return(ft_putchar(c));
    return 0;
}

int ft_printf(const char *str, ...)
{
    int i;
    i = 0;
    int len;
    len = 0;
    va_list ptr;
    va_start(ptr,str);
    if(!str[i])
        return 0;
    while(str[i])
    {
        if(str[i] == '%')
        {
            len += ft_ptr(str[++i],ptr);
            i++;
        }
        else
        {
            len++;
            ft_putchar(str[i]);
            i++;
        }

    }
    return len;
}


#ifndef REAL
# define F	r += ft_printf
#else
# define F	r += printf
#endif

int
	main(void)
{
	int	r;

	r = 0;
	F("Simple test\n");
	F("");
	F("--Format---");
	F("\n");
	F("%d\n", 0);
	F("%d\n", 42);
	F("%d\n", 1);
	F("%d\n", 5454);
	F("%d\n", (int)2147483647);
	F("%d\n", (int)2147483648);
	F("%d\n", (int)-2147483648);
	F("%d\n", (int)-2147483649);
	F("\n");
	F("%x\n", 0);
	F("%x\n", 42);
	F("%x\n", 1);
	F("%x\n", 5454);
	F("%x\n", (int)2147483647);
	F("%x\n", (int)2147483648);
	F("%x\n", (int)-2147483648);
	F("%x\n", (int)-2147483649);
	F("%x\n", (int)0xFFFFFFFF);
	F("\n");
	F("%s\n", "");
	F("%s\n", "toto");
	F("%s\n", "wiurwuyrhwrywuier");
	F("%s\n", NULL);
	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	F("\n--Mixed---\n");
	F("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	F("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	F("\n");
	F("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	printf("written: %d\n", r);
}