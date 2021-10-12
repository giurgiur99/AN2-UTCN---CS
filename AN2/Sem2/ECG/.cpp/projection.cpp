//
//  projection.cpp
//  Lab8_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#include "transform.h"
#include "projection.h"

namespace egc {
    //define the viewport transformation matrix
    //see section 3 from the laboratory work
    mat4 defineViewTransformMatrix(int startX, int startY, int width, int height)
    {
		mat4 viewTransformMatrix;

        viewTransformMatrix.at(0, 0) = width / 2;
        viewTransformMatrix.at(0, 3) = width / 2;
        viewTransformMatrix.at(1, 1) = -height / 2;
        viewTransformMatrix.at(1, 3) = height / 2;

        mat4 viewTranslationMatrix = translate(startX, startY,0);
        viewTransformMatrix = viewTranslationMatrix.operator*(viewTransformMatrix);

        return viewTransformMatrix;
    }
    
    //define the camera transformation matrix
    //see section 4 from the laboratory work
    mat4 defineCameraMatrix(Camera mc)
    {
        mat4 cameraMatrix;
        mat4 cameraMatrix1, cameraMatrix2;

        vec3 w, u, v;
        vec3 g, t;
        g = mc.cameraTarget - mc.cameraPosition;
        t = mc.cameraUp;

        w = - g.normalize();
        u = crossProduct(t, w).normalize();
        v = crossProduct(w, u);

        cameraMatrix1.at(0, 0) = u.x;
        cameraMatrix1.at(0, 1) = u.y;
        cameraMatrix1.at(0, 2) = u.z;

        cameraMatrix1.at(1, 0) = v.x;
        cameraMatrix1.at(1, 1) = v.y;
        cameraMatrix1.at(1, 2) = v.z;

        cameraMatrix1.at(2, 0) = w.x;
        cameraMatrix1.at(2, 1) = w.y;
        cameraMatrix1.at(2, 2) = w.z;

        cameraMatrix2.at(0, 3) = -mc.cameraPosition.x;
        cameraMatrix2.at(1, 3) = -mc.cameraPosition.y;
        cameraMatrix2.at(2, 3) = -mc.cameraPosition.z;

        cameraMatrix = cameraMatrix1.operator*(cameraMatrix2);

	
        return cameraMatrix;

       
    }
    
    //define the projection transformation matrix
    //see section 5 from the laboratory work
    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar)
    {
        mat4 perspectiveProjectionMatrix;

        perspectiveProjectionMatrix.at(0, 0) =  -1 / (aspect * tan(fov / 2));
        perspectiveProjectionMatrix.at(1, 1) =  -1 / (tan(fov / 2));
        perspectiveProjectionMatrix.at(2, 2) = (zFar + zNear) / (zNear - zFar);
        perspectiveProjectionMatrix.at(2, 3) = (2 * zFar * zNear) / (zFar - zNear);
        perspectiveProjectionMatrix.at(3, 2) = 1;
        perspectiveProjectionMatrix.at(3, 3) = 0;

        return perspectiveProjectionMatrix;
    }
    
    //define the perspective divide operation
    //see section 5 from the laboratory work
    void perspectiveDivide(vec4 &iv)
    {
        iv = iv * (1 / iv.w);
    }

    //check if a point should be clipped
    //see section 9 from the laboratory work
    bool clipPointInHomogeneousCoordinate(const egc::vec4 &vertex)
    {
        bool flag1 = false;
        bool flag2 = false;
        bool flag3 = false;

        if (-vertex.w <= vertex.x && vertex.x <= vertex.w)
            flag1 = true;

        if (-vertex.w <= vertex.y && vertex.y <= vertex.w)
            flag2 = true;

        if (-vertex.w <= vertex.z && vertex.z <= vertex.w)
            flag3 = true;
               
        if (flag1 && flag2 && flag3)
            return false;
        else return true;
    }

    //check if a triangle should be clipped
    //clip only those triangles for which all vertices are outside the viewing volume
    bool clipTriangleInHomegeneousCoordinates(const std::vector<egc::vec4> &triangle)
    {
        bool flag1 = false;
        bool flag2 = false;
        bool flag3 = false;
        if (clipPointInHomogeneousCoordinate(triangle.at(0)))
            flag1 = true;
        if (clipPointInHomogeneousCoordinate(triangle.at(1)))
            flag2 = true;
        if (clipPointInHomogeneousCoordinate(triangle.at(2)))
            flag3 = true;
        if (flag1 && flag2 && flag3)
            return false;
        else return true;

    }

    //compute the normal vector to a triangle
    //see section 7 from the laboratory work
    egc::vec3 findNormalVectorToTriangle(const std::vector<egc::vec4> &triangle)
    {
        egc::vec3 n;
        n = crossProduct(triangle.at(1) - triangle.at(0), triangle.at(2) - triangle.at(0));
        n = n.normalize();
        return n;
    }

    //compute the coordinates of the triangle's center
    //(we will use this point to display the normal vector)
    egc::vec4 findCenterPointOfTriangle(const std::vector<egc::vec4> &triangle)
    {
        egc::vec4 triangleCenter;
        triangleCenter.x = (triangle.at(0).x + triangle.at(1).x + triangle.at(2).x) / 3;
        triangleCenter.y = (triangle.at(0).y + triangle.at(1).y + triangle.at(2).y) / 3;
        triangleCenter.z = (triangle.at(0).z + triangle.at(1).z + triangle.at(2).z) / 3;
        triangleCenter.w = (triangle.at(0).w + triangle.at(1).w + triangle.at(2).w) / 3;
        return triangleCenter;
    }

    //check if the triangle is visible (front facing)
    //see section 8 from the laboratory work
    bool isTriangleVisible(const std::vector<egc::vec4> &triangle, const egc::vec3 &normalVector)
    {
        Camera mc;
        mc.cameraTarget = triangle.at(0);
        vec3 v = mc.cameraTarget - mc.cameraPosition;
        
        if (dotProduct(v, normalVector) >= 0)
            return false;
        else return true;
    }

    //display the normal vector of a triangle
    //see section 7 from the laboratory work
    //use the SDL_RenderDrawLine to draw the normal vector
	void displayNormalVectors(egc::vec3 &normalVector, egc::vec4 &triangleCenter, SDL_Renderer *renderer, egc::mat4 viewTransformMatrix, egc::mat4 perspectiveMatrix)
    {
        float offset = 0.05f;
        vec4 intermediateVector = vec4(normalVector.x, normalVector.y, normalVector.z, 1);
        vec4 secondPoint = triangleCenter + intermediateVector * offset;

        triangleCenter = perspectiveMatrix * triangleCenter;
        perspectiveDivide(triangleCenter);
        triangleCenter = viewTransformMatrix * triangleCenter;

        secondPoint = perspectiveMatrix * secondPoint;
        perspectiveDivide(secondPoint);
        secondPoint = viewTransformMatrix * secondPoint;

        SDL_SetRenderDrawColor(renderer, 96, 96, 96, 0);
        SDL_RenderDrawLine(renderer, triangleCenter.x, triangleCenter.y, secondPoint.x, secondPoint.y);
    }
}
