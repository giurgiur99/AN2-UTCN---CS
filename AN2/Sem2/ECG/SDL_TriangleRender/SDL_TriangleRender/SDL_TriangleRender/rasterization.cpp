#include "rasterization.h"

namespace egc {

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma)
	{
		//TO DO - Compute alfa, beta and gamma => we use the function's input parameters as the return mechanism
		//Store the final results in the input parameters

		float point_x = pixel.x;
		float point_y = pixel.y;

		float FBC = (triangleVertices[1].y - triangleVertices[2].y) * point_x +
			(triangleVertices[2].x - triangleVertices[1].x) * point_y +
			+triangleVertices[1].x * triangleVertices[2].y -
			triangleVertices[2].x * triangleVertices[1].y;

		float FBCA = (triangleVertices[1].y - triangleVertices[2].y) * triangleVertices[0].x +
			(triangleVertices[2].x - triangleVertices[1].x) * triangleVertices[0].y +
			+triangleVertices[1].x * triangleVertices[2].y -
			triangleVertices[2].x * triangleVertices[1].y;

		alpha = FBC / FBCA;

		float FAC = (triangleVertices[0].y - triangleVertices[2].y) * point_x +
			(triangleVertices[2].x - triangleVertices[0].x) * point_y +
			+triangleVertices[0].x * triangleVertices[2].y -
			triangleVertices[2].x * triangleVertices[0].y;

		float FACB = (triangleVertices[0].y - triangleVertices[2].y) * triangleVertices[1].x +
			(triangleVertices[2].x - triangleVertices[0].x) * triangleVertices[1].y +
			+triangleVertices[0].x * triangleVertices[2].y -
			triangleVertices[2].x * triangleVertices[0].y;

		beta = FAC / FACB;

		gamma = 1 - alpha - beta;
	}

	void rasterizeTriangle(SDL_Renderer* renderer, const std::vector<egc::vec4>& triangleVertices, const std::vector<egc::vec4>& triangleColors) {
		//TO DO - Implement the triangle rasterization algorithm

		int a_x = triangleVertices.at(0).x;
		int b_x = triangleVertices.at(1).x;
		int c_x = triangleVertices.at(2).x;

		int a_y = triangleVertices.at(0).y;
		int b_y = triangleVertices.at(1).y;
		int c_y = triangleVertices.at(2).y;

		int max_x, max_y, min_x, min_y;

		max_x = std::max(a_x, std::max(b_x, c_x));
		max_y = std::max(a_y, std::max(b_y, c_y));

		min_x = std::min(a_x, std::min(b_x, c_x));
		min_y = std::min(a_y, std::min(b_y, c_y));

		float alpha, gamma, beta;

		for (int x = min_x; x <= max_x; x++) {

			for (int y = min_y; y <= max_y; y++) {

				vec2 point;
				point.x = x;
				point.y = y;

				computeAlphaBetaGamma(triangleVertices, point, alpha, beta, gamma);

				if (alpha > 0 && alpha < 1 && beta > 0 && beta < 1 && gamma > 0 && gamma < 1) {

					egc::vec4 color = triangleColors.at(0) * alpha + triangleColors.at(1) * beta +
						triangleColors.at(2) * gamma;

					SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
					SDL_RenderDrawPoint(renderer, x, y);
				}
			}
		}
	}

}