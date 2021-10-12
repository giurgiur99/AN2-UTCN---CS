#include "clip.h"
#include "transform.h"

namespace egc {
	
	//Cyrus-Beck clipping algorithm
	//clipWindow specifies the vertices that define the clipping area in conterclockwise order
	//and can represent any convex polygon

	//clipWindow.push_back(vec3(250.0f, 200.0f, 1.0f)); --> stanga sus
	//clipWindow.push_back(vec3(250.0f, 400.0f, 1.0f)); --> stanga jos
	//clipWindow.push_back(vec3(550.0f, 400.0f, 1.0f)); --> dreapta jos
	//clipWindow.push_back(vec3(550.0f, 200.0f, 1.0f)); --> dreapta sus

	//function returns -1 if the line segment cannot be clipped

	//           [250,200]        [550,200]  
	//clipwindow.at(0) ____________clipwindow.at(3)
	//			      |		E3	   |
	//			  E0  |			   |E2
	//				  |			   |
	//clipwindow.at(1)_____________ clipwindow.at(2)
	//           [250,400]  E1    [550,400]


	float min(float x, float y)
	{
		if (x < y)
			return x;
		else return y;
	}

	float max(float x, float y)
	{
		if (x > y)
			return x;
		else return y;
	}

	bool isPointInsideClippingWindow(vec3& p1, std::vector<vec3> clipWindow)
	{
		if (p1.x >= clipWindow.at(0).x && p1.x <= clipWindow.at(2).x && p1.y >= clipWindow.at(0).y && p1.y <= clipWindow.at(2).y)
			return true;
		return false;
	}

	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		//TO DO - implement the Cyrus-Beck line clipping algorithm - consult the laboratory work

		std::vector<vec3> normals;
		for (int i = 0; i < 3; i++)
		{
			vec3 v = clipWindow.at(i + 1) - clipWindow.at(i);
			vec3 normal;
			normal = rotate(90) * v;
			normal.normalize();
			normals.push_back(normal);
		}
		vec3 v = clipWindow.at(0) - clipWindow.at(3);
		vec3 normal;
		normal = rotate(90) * v;
		normal.normalize();
		normals.push_back(normal);

		float t;
		float PE = 0, PL = 0;
		float tE = 0, tL = 1;
		vec3 PtE, PtL;

		std::vector<vec3> pointOnEdge;
		vec3 PE0 = vec3(250,300,1);
		pointOnEdge.push_back(PE0);
		vec3 PE1 = vec3(400,400,1);
		pointOnEdge.push_back(PE1);
		vec3 PE2 = vec3(550,300,1);
		pointOnEdge.push_back(PE2);
		vec3 PE3 = vec3(400,200,1);
		pointOnEdge.push_back(PE3);
	
		vec3 D = p2 - p1;

		if (p1 == p2)
		{
			if (isPointInsideClippingWindow(p1, clipWindow))
				return 0;
			else return -1;
		}	
		else
		{
			for (int i = 0; i < normals.size(); i++)
			{
				if (dotProduct(normals.at(i), D) != 0)
				{
					t = -(dotProduct(normals.at(i), p1 - pointOnEdge.at(i)) / dotProduct(normals.at(i), D));
					
						if (dotProduct(normals.at(i), D) < 0)
							tE = max(tE, t);

						if (dotProduct(normals.at(i), D) > 0)
						    tL = min(tL, t);
				}
			}
		}
			
		if (tE > tL)
			return -1;
		else
		{
			PtE = p1 + (p2 - p1) * tE;
			PtL = p1 + (p2 - p1) * tL;
			p1 = PtE;
			p2 = PtL;	
		}	
	}
}

