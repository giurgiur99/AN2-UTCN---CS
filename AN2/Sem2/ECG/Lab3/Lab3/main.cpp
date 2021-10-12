//
//  main.cpp
//  Lab3
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "testMatrix.h"
#include "mat3.h"
#include "mat4.h"
#include "../../Lab4/testTransform.h"
using namespace std;

int main(int argc, const char * argv[])
{
	int nrOfErrors = 0;

	nrOfErrors += egc::testMat3Implementation();
	nrOfErrors += egc::testMat4Implementation();

	nrOfErrors += egc::test2DTransformImplementation();
	nrOfErrors += egc::test3DTransformImplementation();

	cout << "Number of errors: " << nrOfErrors << endl;

	getchar();

	return 0;
}
