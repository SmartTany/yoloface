#include "yoloface.h"

namespace YOLOv3
{
	Detecting::Detecting()
	{
		string ConfigPath = "../cfg/yolov3-face.cfg";                      //cfg
		string WeightsPath = "../backup/yolov3-face_last.weights";         //weights
		string MetaDataPath = "../cfg/yolov3-face.data";                    //data
	

		mpNetwork = load_network((char *)ConfigPath.data(),(char *)WeightsPath.data(),0);
		mData = get_metadata((char *)MetaDataPath.data());
		mpTransMethod = new TransMethod;
	}

	void Detecting::Detect(cv::Mat Frame, vector<yoloresult>& vDetectResults)
	{
		vDetectResults.clear();
		image Image = mpTransMethod->MattoImage(Frame);

		int* pCount = new int(0);
		network_predict_image(mpNetwork,Image);
		detection* pDetection = get_network_boxes(mpNetwork,Image.w,Image.h,0.5,0.5,nullptr,0,pCount,0);
		do_nms_obj(pDetection,*pCount,mData.classes,0.45);

		for (size_t j = 0; j < *pCount; j++)
		{
			for (size_t i = 0; i < mData.classes; i++)
			{
				if (pDetection[j].prob[i] > 0)
				{
					yoloresult Result;
					Result.mName = mData.names[i];
					Result.mConfidence = pDetection[j].prob[i];
					Result.mTop = (pDetection[j].bbox.y - pDetection[j].bbox.h / 2);
					Result.mBottom = (pDetection[j].bbox.y + pDetection[j].bbox.h / 2);
					Result.mLeft = (pDetection[j].bbox.x - pDetection[j].bbox.w / 2);
					Result.mRight = (pDetection[j].bbox.x + pDetection[j].bbox.w / 2);
					vDetectResults.push_back(Result);
				}
			}
		}
	}
    void Detecting::DrawResult(cv::Mat& Image, vector<yoloresult> Result)
    {  
		for (vector<yoloresult>::iterator it = Result.begin(); it != Result.end(); it++)
		{
			cv::Point2f PointA(it->mLeft,it->mTop);
			cv::Point2f PointB(it->mRight,it->mBottom);
			cv::Point2f PointT(it->mLeft,it->mBottom+5);
			cv::rectangle(Image,PointA,PointB,cv::Scalar(0,0,255),1,1,0);
			cv::putText(Image,"face", PointT,cv::FONT_HERSHEY_DUPLEX,0.3,(255,255,255),1);
		}
    }
}







