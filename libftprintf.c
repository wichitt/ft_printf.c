/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wamonvor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:58:51 by wamonvor          #+#    #+#             */
/*   Updated: 2023/03/14 14:26:06 by wamonvor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

void ft_putchar(char c) {
    write(1, &c, 1);
}

void ft_puts(const char *s) {
    while (*s != '\0') {
        ft_putchar(*s);
        s++;
    }
}

void ft_putnbr(int n) {
    if (n < 0) {
        ft_putchar('-');
        n = -n;
    }
    if (n >= 10) {
        ft_putnbr(n / 10);
        ft_putchar(n % 10 + '0');
    } else {
        ft_putchar(n + '0');
    }
}

void ft_putdouble(double n, int precision) {
    long int_part = (long)n;
    long frac_part = (long)((n - int_part) * pow(10, precision));
    ft_putnbr(int_part);
    ft_putchar('.');
    if (frac_part < 0) {
        frac_part = -frac_part;
    }
    if (frac_part == 0) {
        for (int i = 0; i < precision; i++) {
            ft_putchar('0');
        }
    } else {
        int digits[precision];
        int i = 0;
        while (frac_part > 0) {
            digits[i] = frac_part % 10;
            frac_part /= 10;
            i++;
        }
        for (int j = i - 1; j >= 0; j--) {
            ft_putchar(digits[j] + '0');
        }
    }
}

void ft_handle_d(va_list args) {
    int value = va_arg(args, int);
    ft_putnbr(value);
}

void ft_handle_f(va_list args) {
    double value = va_arg(args, double);
    ft_putdouble(value, 6);
}

void ft_handle_s(va_list args) {
    char *value = va_arg(args, char *);
    ft_puts(value);
}

void ft_puthex(unsigned int n) {
    char hex[] = "0123456789ABCDEF";
    if (n >= 16) {
        ft_puthex(n / 16);
    }
    ft_putchar(hex[n % 16]);
}

void ft_handle_X(va_list args) {
    unsigned int value = va_arg(args, unsigned int);
    ft_puthex(value);
}

void ft_handle_c(va_list args) {
    char value = (char)va_arg(args, int);
    ft_putchar(value);
}
void ft_handle_s(va_list args) {
    char *value = va_arg(args, char *);
    ft_puts(value);
}

void ft_handle_p(va_list args) {
    void *value = va_arg(args, void *);
    ft_printf("%p", value);
}

void ft_handle_i(va_list args) {
    int value = va_arg(args, int);
    ft_putnbr(value);
}

void ft_handle_u(va_list args) {
    unsigned int value = va_arg(args, unsigned int);
    ft_putnbr(value);
}

void ft_handle_x(va_list args) {
    unsigned int value = va_arg(args, unsigned int);
    ft_puthex(value, 0);
}

void ft_handle_percent(va_list args) {
    ft_putchar('%');
}


void ft_printf(const char *format, ...) {
    va_list args;
    int i;

    va_start(args, format);
    i = 0;
    while (format[i] != '\0') {
        if (format[i] == '%') {
            i++;
            if (format[i] == 'd') {
                ft_handle_d(args);
            }
            else if (format[i] == 'f') {
                ft_handle_f(args);
            }
            else if (format[i] == 's') {
                ft_handle_s(args);
            }
            else if (format[i] == 'X') {
                ft_handle_X(args);
            } else if (format[i] == 'c') {
            ft_handle_c(args);
        } else if (format[i] == 's') {
            ft_handle_s(args);
        } else if (format[i] == 'p') {
            ft_handle_p(args);
        } else if (format[i] == 'i') {
            ft_handle_i(args);
        } else if (format[i] == 'u') {
            ft_handle_u(args);
        } else if (format[i] == 'x') {
            ft_handle_x(args);
        } else if (format[i] == '%') {
            ft_handle_percent(args);
        }
            ft_putchar(format[i]);
        } else {
            ft_putchar(format[i]);
        }
        i++;
    }
    va_end(args);
}
