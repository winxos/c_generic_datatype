#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#ifndef bool
typedef u8 				bool;
#endif
#ifndef NULL
#define NULL 	(0)
#endif
#define TRUE 1
#define FALSE 0