#ifndef IO_H
#define IO_H

#ifdef __GNUC__
#include <stddef.h>
#include <stdint.h>
#endif

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

#endif
