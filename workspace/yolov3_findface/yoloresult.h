#pragma once
#ifndef __YOLORESULT_H
#define __YOLORESULT_H

#include <string>

using namespace std;

namespace YOLOv3
{
class yoloresult
{
public:
	string mName;
	float mConfidence;
	float mTop;
	float mBottom;
	float mLeft;
	float mRight;

	bool unknown = false;

};
}




#endif

