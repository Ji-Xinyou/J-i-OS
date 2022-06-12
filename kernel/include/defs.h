#ifndef __DEFS_H
#define __DEFS_H

#include "types.h"

// VGA.c
void VGA_clear(const u8, const u8);
void VGA_putc(const char, const u8, const u8);
void VGA_putstr(const char*, const u8, const u8);
void VGA_putint(const int);
u16  get_cpos();
void set_cpos(u8, u8);
void show_cursor();
void hide_cursor();
void advance_cpos();

// port.c
u8 r_port(u16);
void w_port(u16, u8);

// exit.c
void exitvm(u32);

// uart.c
void uart_init();
void uart_putstr(const char*);

// utils
char* itoa(int, char*, unsigned);

#endif