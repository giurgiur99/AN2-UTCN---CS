//
//  projection.cpp
//  Lab8_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#include "projection.h"

namespace egc {
    //define the viewport transformation matrix
    //see section 3 from the laboratory work
    mat4 defineViewTransformMatrix(int startX, int startY, int width, int height)
    {
		mat4 viewTransformMatrix;
		mat4 SMT = mat4();
		mat4 T = translate((float)startX, (float)startY, 0);
		SMT.at(0, 0) = width / 2.0;
		SMT.at(1, 1) = -height / 2.0;
		SMT.at(0, 3) = width / 2.0;
		SMT.at(1, 3) = height / 2.0;

		viewTransformMatrix = T * SMT;

        return viewTransformMatrix;
    }
    
    //define the camera transformation matrix
    //see section 4 from the laboratory work
    mat4 defineCameraMatrix(Camera mc)
    {
		vec3 u, v, w;
		vec3 e, g, t;
		e = mc.cameraPosition;
		g = mc.cameraTarget - mc.cameraPosition;
		t = mc.cameraUp;

		w = -(g.normalize());
		u = crossProduct(t, w).normalize();
		v = crossProduct(w, u);

		mat4 cameraMatrix, a, b;
		a = mat4(); b = mat4();
		a.at(0, 0) = u.x;
		a.at(1, 0) = v.x;
		a.at(2, 0) = w.x;

		a.at(0, 1) = u.y;
		a.at(1, 1) = v.y;
		a.at(2, 1) = w.y;

		a.at(0, 2) = u.z;
		a.at(1, 2) = v.z;
		a.at(2, 2) = w.z;

		b.at(0, 3) = -e.x;
		b.at(1, 3) = -e.y;
		b.at(2, 3) = -e.z;
		
		cameraMatrix = a * b;
        return cameraMatrix;
    }
    
    //define the projection transformation matrix
    //see section 5 from the laboratory work
    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar)
    {
        mat4 Mper = mat4();
		double tangent = -1 / tan(fov / 2.0);
		
		Mper.at(0, 0) = tangent / aspect;
		Mper.at(1, 1) = tangent;
		Mper.at(2, 2) = (zNear + zFar) / (zNear - zFar);
		Mper.at(3, 3) = 0;
		Mper.at(2, 3) = (2 * zNear*zFar) / (zFar - zNear);
		Mper.at(3, 2) = 1;

        return Mper;
    }
    
    //define the perspective divide operation
    //see section 5 from the laboratory work
    void perspectiveDivide(vec4 &iv)
    {
		float z = iv.w;
		iv = iv * (1 / z);
    }

    //check if a point should be clipped
    //see section 9 from the laboratory work
    bool clipPointInHomogeneousCoordinate(const egc::vec4 &vertex)
    {
		float w = abs(vertex.w);


		if (vertex.x < -w || vertex.x > w || vertex.y < -w || vertex.y > w || vertex.z < -w || vertex.z > w) return true;

        return false;
    }

    //check if a triangle should be clipped
    //clip only those triangles for which all vertices are outside the viewing volume
    bool clipTriangleInHomegeneousCoordinates(const std::vector<egc::vec4> &triangle)
    {
		float w;
		for (int i = 0; i < triangle.size(); i++) {
			w = abs(triangle.at(i).w);
			if (triangle.at(i).x < -w || triangle.at(i).x > w || triangle.at(i).y < -w || triangle.at(i).y > w || triangle.at(i).z < -w || triangle.at(i).z > w) return true;
		}
        return false;
    }

    //compute the normal vector to a triangle
    //see section 7 from the laboratory work
    egc::vec3 findNormalVectorToTriangle(const std::vector<egc::vec4> &triangle)
    {
        egc::vec3 n;
		egc::vec4 edge1, edge2;
		egc::vec3 e1, e2;
		edge1 = triangle.at(1) - triangle.at(0);
		edge2 = triangle.at(2) - triangle.at(0);

		e1 = vec3(edge1.x, edge1.y, edge1.z);
		e2 = vec3(edge2.x, edge2.y, edge2.z);

        return crossProduct(e1, e2);
    }

    //compute the coordinates of the triangle's center
    //(we will use this point to display the normal vector)
    egc::vec4 findCenterPointOfTriangle(const std::vector<egc::vec4> &triangle)
    {
		egc::vec4 triangleCenter = (triangle.at(0) + triangle.at(1) + triangle.at(2)) * (1/3);
        return triangleCenter;
    }

    //check if the triangle is visible (front facing)
    //see section 8 from the laboratory work
    bool isTriangleVisible(const std::vector<egc::vec4> &triangle, const egc::vec3 &normalVector)
    {
		if (dotProduct(triangle.at(0), normalVector) > 0 || dotProduct(triangle.at(1), normalVector) > 0 || dotProduct(triangle.at(2), normalVector) > 0) return false;
        return true;
    }

    //display the normal vector of a triangle
    //see section 7 from the laboratory work
    //use the SDL_RenderDrawLine to draw the normal vector
	void displayNormalVectors(egc::vec3 &normalVector, egc::vec4 &triangleCenter, SDL_Renderer *renderer, egc::mat4 viewTransformMatrix, egc::mat4 perspectiveMatrix)
    {
		normalVector.normalize();
		egc::vec4 secondPoint;
		secondPoint.x = triangleCenter.x + normalVector.x * 0.1;
		secondPoint.y = triangleCenter.y + normalVector.y * 0.1;
		secondPoint.z = triangleCenter.z + normalVector.z * 0.1;
		secondPoint.w = triangleCenter.w;

		secondPoint = perspectiveMatrix * secondPoint;
		perspectiveDivide(secondPoint);
		secondPoint = viewTransformMatrix * secondPoint;

		triangleCenter = perspectiveMatrix * triangleCenter;
		perspectiveDivide(triangleCenter);
		triangleCenter = viewTransformMatrix * triangleCenter;

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 1);

		SDL_RenderDrawLine(renderer, triangleCenter.x, triangleCenter.y, secondPoint.x, secondPoint.y);
    }
}
