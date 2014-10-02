#ifndef _CPlyInfo_HG_
#define _CPlyInfo_HG_

#include <string>

class CPlyInfo
{
public:
	CPlyInfo();
	~CPlyInfo();
	int numberOfVertices;
	int numberOfElements;
	int vertexBufferStartIndex;
	int indexBufferStartIndex;
	float extent;
	std::wstring plyFileName;
};

#endif