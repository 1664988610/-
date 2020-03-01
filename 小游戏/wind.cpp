#include "wind.h"

void wind1::move()
{
	y += mov;
	fla = (fla + 1) % 12;
}

void wind2::move()
{
	x += mov;
	fla = (fla + 1) % 12;
}

void wind3::move()
{
	y -= mov;
	fla = (fla + 1) % 12;
}

void wind4::move()
{
	x -= mov;
	fla = (fla + 1) % 12;
}