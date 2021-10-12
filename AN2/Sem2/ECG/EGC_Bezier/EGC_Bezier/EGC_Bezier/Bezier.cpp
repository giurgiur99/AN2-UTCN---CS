#include "Bezier.h"
#include "math.h"
#include <vector>

//Return the value of P(t), where t is in [0,1]
vec2 getParametricPoint(float t, vec2 p0, vec2 p1) {
	//P(t) = (1 - t)*P0 + t*P1
	vec2 point;
	point = p0.operator*(1 - t) + p1.operator*(t);

	return point;
}

//Paint the pixels that are on the line P0P1
void drawParametricLinePoints(vec2 p0, vec2 p1, SDL_Renderer* renderer) {
	//Hint: To paint a single pixel, you can use the function: SDL_RenderDrawPoint(renderer, x, y)
	for (float t = 0; t <= 1; t += 0.0001)
	{
		auto point = getParametricPoint(t, p0, p1);
		SDL_RenderDrawPoint(renderer, point.x, point.y);
	}
	
}

//Return the value of B(t), where t is in [0,1]. The value of B(t) is computed by taking into account all the 
//controll points contained within the input vecto
vec2 getBezierPoint(std::vector<vec2> controlPoints, float t) {
	vec2 point;

	return point;
}

//Paint the pixels that are on the Bezier curve defined by the given control points
void drawBezierPoints(std::vector<vec2> controlPoints, SDL_Renderer* renderer) {

}
