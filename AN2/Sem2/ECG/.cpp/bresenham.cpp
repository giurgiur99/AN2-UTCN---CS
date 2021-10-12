#include "bresenham.h"
#include "math.h"

//Detects in which octant a line is situated
int getOctant(BresenhamLine line) {

	int dY = (line.endY - line.startY);
	int dX = (line.endX - line.startX);

	//Slope		
	float m = abs(dY) / (float)abs(dX);
	//first octant
	if (m <= 1 && dX > 0 && dY <= 0) return 1;
	//second octant
	if (m >= 1 && dX > 0 && dY < 0) return 2;
	//third octant
	if (m >= 1 && dX <= 0 && dY < 0) return 3;
	//fourth octant
	if (m < 1 && dX < 0 && dY <= 0) return 4;
	//fifth octant
	if (m < 1 && dX < 0 && dY >= 0) return 5;
	//sixth octant
	if (m >= 1 && dX <= 0 && dY > 0) return 6;
	//seventh octant
	if (m >= 1 && dX >= 0 && dY > 0) return 7;
	//eighth octant
	if (m <= 1 && dX >= 0 && dY > 0) return 8;

	return 0;
}

//Draws a new raster line using Bresenham's algorithm
void BresenhamDraw(BresenhamLine line, SDL_Renderer* renderer) {
	int startX = 0;
	int startY = 0;

	int endX = 0;
	int endY = 0;

	int currentX = 0;
	int currentY = 0;

	int dy = abs(line.endY - line.startY);
	int dx = abs(line.endX - line.startX);

	int d, inc1, inc2;

	int octant = getOctant(line);

	switch (octant)
	{
	case 1: // m<=1

		startY = currentY = line.startY;
		endY = line.endY;

		startX = currentX = line.startX;
		endX = line.endX;

		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);
		d = 2 * dy - dx;

		while (currentX < endX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, currentX, currentY);
			currentX++;

			if (d < 0) d = d + inc1;
			else
			{
				d = d + inc2;
				currentY--;
			}
		}
		break;
	case 2: //m >=1
		startX = line.startX;
		currentX = line.startX;

		startY = line.startY;
		currentY = line.startY;

		endX = line.endX;
		endY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (currentX < endX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, currentX, currentY);
			currentY--;

			if (d < 0) d = d + inc1;
			else
			{
				d = d + inc2;
				currentX++;
			}
		}
		break;
	case 3: // m>1
		startX = line.startX;
		currentX = line.startX;

		startY = line.startY;
		currentY = line.startY;

		endX = line.endX;
		endY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (currentX > endX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, currentX, currentY);
			currentY--;

			if (d < 0) d = d + inc1;
			else
			{
				d = d + inc2;
				currentX--;
			}
		}
		break;

		break;
	case 4: //m<1
		startX = line.startX;
		currentX = line.startX;

		startY = line.startY;
		currentY = line.startY;

		endX = line.endX;
		endY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (currentX > endX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, currentX, currentY);
			currentX--;

			if (d < 0) d = d + inc1;
			else
			{
				d = d + inc2;
				currentY--;
			}
		}

		break;
	case 5: // m <1
		startX = line.startX;
		currentX = line.startX;

		startY = line.startY;
		currentY = line.startY;

		endX = line.endX;
		endY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (currentX > endX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, currentX, currentY);
			currentX--;

			if (d < 0) d = d + inc1;
			else
			{
				d = d + inc2;
				currentY++;
			}
		}
		break;
	case 6: // m>1
		startX = line.startX;
		currentX = line.startX;

		startY = line.startY;
		currentY = line.startY;

		endX = line.endX;
		endY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (currentX > endX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, currentX, currentY);
			currentY++;

			if (d < 0) d = d + inc1;
			else
			{
				d = d + inc2;
				currentX--;
			}
		}
		break;
	case 7: // m>1
		startX = line.startX;
		currentX = line.startX;

		startY = line.startY;
		currentY = line.startY;

		endX = line.endX;
		endY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (currentX < endX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, currentX, currentY);
			currentY++;

			if (d < 0) d = d + inc1;
			else
			{
				d = d + inc2;
				currentX++;
			}
		}

		break;
	case 8:
		startX = line.startX;
		currentX = line.startX;

		startY = line.startY;
		currentY = line.startY;

		endX = line.endX;
		endY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (currentX < endX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, currentX, currentY);
			currentX++;

			if (d < 0) d = d + inc1;
			else
			{
				d = d + inc2;
				currentY++;
			}
		}
		break;

	default:
		break;
	}
}

void plot_points(SDL_Renderer* renderer, BresenhamCircle circle, int x, int y)
{
	SDL_RenderDrawPoint(renderer, x + circle.centerX, y + circle.centerY);
	SDL_RenderDrawPoint(renderer, x + circle.centerX, -y + circle.centerY);
	SDL_RenderDrawPoint(renderer, -x + circle.centerX, y + circle.centerY);
	SDL_RenderDrawPoint(renderer, -x + circle.centerX, -y + circle.centerY);
	SDL_RenderDrawPoint(renderer, y + circle.centerX, x + circle.centerY);
	SDL_RenderDrawPoint(renderer, -y + circle.centerX, x + circle.centerY);
	SDL_RenderDrawPoint(renderer, y + circle.centerX, -x + circle.centerY);
	SDL_RenderDrawPoint(renderer, -y + circle.centerX, -x + circle.centerY);


}
//Draws a new raster circle using Bresenham's algorithm
void BresenhamDraw(BresenhamCircle circle, SDL_Renderer* renderer) {

	int currentY = circle.radius;
	int d = 1 / 4 - circle.radius;

	for (int currentX = 0; currentX < ceil(circle.radius / sqrt(2)); currentX++)
	{
		plot_points(renderer, circle, currentX, currentY);
		d = d + 2 * currentX + 1;

		if (d > 0)
		{
			d = d + (2 - 2 * currentY);
			currentY--;
		}
	}
}