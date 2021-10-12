//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"
#include "transform.h"

using namespace egc;

SDL_Renderer* windowRenderer;
// define rectangle vertices
vec3 P1(100, 100, 1), P2(400, 200, 1), P3(100, 200, 1), P4(400, 100, 1);

//define window dimensions
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Event currentEvent;

SDL_Rect rectangleCoordinates = { 100, 100, 200, 200 };

bool quit = false;

int mouseX, mouseY;

bool initWindow()
{
	bool success = true;

	//Try to initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL initialization failed" << std::endl;
		success = false;
	}
	else {
		//Try to create the window
		window = SDL_CreateWindow("SDL Hello World Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

		if (window == NULL)
		{
			std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// Create a renderer for the current window
			windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (windowRenderer == NULL)
			{
				std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				//Set background color
				SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);

				//Apply background color
				SDL_RenderClear(windowRenderer);
			}

		}
	}

	return success;
}

void setPoints(mat3 matrix)
{
	P1 = matrix * P1;
	P2 = matrix * P2;
	P3 = matrix * P3;
	P4 = matrix * P4;
}

void destroyWindow()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	if (!initWindow())
	{
		std::cout << "Failed to initialize" << std::endl;
		return -1;
	}


	while (!quit) {
		//Handle events on queue
		if (SDL_WaitEvent(&currentEvent) != 0)
		{
			//User requests quit
			if (currentEvent.type == SDL_QUIT)
			{
				quit = true;
			}

			//Mouse event -> pressed button
			if (currentEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				if (currentEvent.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&mouseX, &mouseY);
					std::cout << "Mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
				}
			}

			//Mouse event -> mouse movement
			if (currentEvent.type == SDL_MOUSEMOTION)
			{
				if (currentEvent.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&mouseX, &mouseY);
					std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
				}
			}
			vec3 intersection((P1.x + P2.x) / 2, (P1.y + P2.y) / 2, 1);
			mat3 matrix1, matrix2, result;
			vec3 cP1 = vec3(P1);
			//Keyboard event
			if (currentEvent.type == SDL_KEYDOWN)
			{
				switch (currentEvent.key.keysym.sym)
				{
				case SDLK_LEFT:
				{
					matrix1 = translate(-intersection.x, -intersection.y);
					matrix2 = rotate(-10);
					setPoints(matrix1);
					setPoints(matrix2);
					matrix1 = translate(intersection.x, intersection.y);
					setPoints(matrix1);
					printf("%f,%f\n", intersection.x, intersection.y);
					break;
				}
				case SDLK_RIGHT:
				{
					matrix1 = translate(-intersection.x, -intersection.y);
					matrix2 = rotate(10);
					setPoints(matrix1);
					setPoints(matrix2);
					matrix1 = translate(intersection.x, intersection.y);
					setPoints(matrix1);
					printf("%f,%f\n", intersection.x, intersection.y);
					break;
				}
				case SDLK_DOWN:
				{
					printf("%f,%f\n", P1.x, P1.y);
					matrix1 = translate(-P1.x, -P1.y);
					matrix2 = scale(0.95, 0.95);
					setPoints(matrix1);
					setPoints(matrix2);
					matrix1 = translate(cP1.x, cP1.y);
					setPoints(matrix1);
					break;
				}
				case SDLK_UP:
				{
					printf("%f,%f\n", P1.x, P1.y);
					matrix1 = translate(-P1.x, -P1.y);
					matrix2 = scale(1.05, 1.05);
					setPoints(matrix1);
					setPoints(matrix2);
					matrix1 = translate(cP1.x, cP1.y);
					setPoints(matrix1);
					break;
				}
				default:
				{
					break;
				}
				}
			}
			SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
			SDL_RenderClear(windowRenderer);

			SDL_SetRenderDrawColor(windowRenderer, 255, 0, 0, 255);

			SDL_RenderDrawLine(windowRenderer, P1.x, P1.y, P3.x, P3.y);
			SDL_RenderDrawLine(windowRenderer, P1.x, P1.y, P4.x, P4.y);
			SDL_RenderDrawLine(windowRenderer, P2.x, P2.y, P3.x, P3.y);
			SDL_RenderDrawLine(windowRenderer, P2.x, P2.y, P4.x, P4.y);

			//SDL_SetRenderDrawColor(windowRenderer,0 , 0, 255, 255);
			//SDL_RenderDrawLine(windowRenderer, P1.x, P1.y, P2.x, P2.y);
			//SDL_RenderDrawLine(windowRenderer, P4.x, P4.y, P3.x, P3.y);
			SDL_RenderPresent(windowRenderer);


		}
	}

	destroyWindow();
	return 0;
}
