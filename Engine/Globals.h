#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "MemLeaks.h"
#include "SDL/include/SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__)

void log(const char file[], int line, const char* format, ...);

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define CLAMP( v, min, max ) ( MAX(min, MIN(v, max)) )
#define DEG2RAD(deg) (deg * float(M_PI) / 180.0f)
#define ZTOY(z, angle) ( cos(DEG2RAD(angle)) * z )

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Useful typedefs ---------
typedef unsigned int uint;

// Deletes a buffer
#define RELEASE( x ) \
	{									  \
	   if( x != nullptr )   \
	   {						      \
		 delete x;                  \
		 x = nullptr;             \
	   }                      \
	}

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{                              \
	   if( x != nullptr )              \
	   {                            \
		   delete[] x;                \
		   x = nullptr;                    \
		 }                            \
							  \
	 }

// Configuration -----------
#define SCREEN_SIZE 4
#define SCREEN_WIDTH 288
#define SCREEN_HEIGHT 224
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Simpsons Arcade"

#endif //__GLOBALS_H__