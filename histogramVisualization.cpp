#include "common.h"
#define WIDTH 800
#define HEIGHT 600
void calculateAndVisualizeHist(Mat src,int bins,int range,char* channel_name)//Mat
{
	printf("\nEntering Function for %s channel\n",channel_name);
	char window_name[10] ;
	sprintf(window_name,"Histogram-%s",channel_name);
	
	 int gbins = bins;
     int histSize[] = {gbins};
     float granges[] = { 0, range };
	 const float* ranges[] = { granges};
     MatND hist;
     int channels = {0};
     double maxVal=0;
     int scale =5,intensity,j=0;
     float sum =0,binVal=0;
     
     calcHist( &src, 1, &channels, Mat(), hist, 1, histSize, ranges,true,false );
     maxVal =0;
	 minMaxLoc(hist, 0, &maxVal, 0, 0);
	
	 Mat histImg = Mat::zeros(Size(gbins*scale,255), CV_8UC3);
	 
    for( int h = 0; h < gbins; h++ )
	       {
				 binVal = hist.at<float>(h);
				
			   	 intensity = cvRound(binVal*255/maxVal);
			   	 sum+=intensity;
				
			   	 rectangle( histImg, Point(h*scale,256),
				        Point( ((h+1)*scale - 1),256 - intensity),
				        Scalar::all(255),
				        CV_FILLED );
			}
     imshow(window_name,histImg);
     printf("\nLeaving Function for %s channel\n",channel_name);
    
     //return hist;
}

int main (int argc, char const* argv[])
{
	if(argc<2)
	{
		printf("\nUsage ./filename file.ext  \nAbort..\n");
		return 0;
	}
	
	Mat src = imread(argv[1],1);
	
	if(!src.data)
	{
		printf("\nError in input image\nAbort..\n");
		return 0;
	}
	
	int flag=0;
	
	if(argc>=3)
	{
		flag = atoi(argv[2]);
	}	
	Mat src_image;
	Mat t[3],temp;
	
	if(src.cols>WIDTH||src.rows>HEIGHT)
	{
		resize(src,src_image,Size(WIDTH,HEIGHT));
		t[0] = Mat(WIDTH,HEIGHT,CV_8U);
		t[1] = Mat(WIDTH,HEIGHT,CV_8U);
		t[2] = Mat(WIDTH,HEIGHT,CV_8U);
		temp = Mat(WIDTH,HEIGHT,CV_8U);
	}	
	else
	{
		src.copyTo(src_image);
		t[0] = Mat(src.size(),CV_8U);
		t[1] = Mat(src.size(),CV_8U);
		t[2] = Mat(src.size(),CV_8U);
		temp = Mat(src.size(),CV_8U);
		
	}	
		
	imshow("Original-resized",src_image);
	waitKey(0);
	
	if(flag!=1&&flag!=2)
	{
		split(src_image,t);
		calculateAndVisualizeHist(t[0],256,256,"blue");
		
		calculateAndVisualizeHist(t[1],256,256,"green");
	
		calculateAndVisualizeHist(t[2],256,256,"red");
	}
	else if(flag==1)
	{
		cvtColor(src_image,temp,CV_BGR2HSV);
		split(temp,t);
		calculateAndVisualizeHist(t[0],256,256,"Hue");
		
		calculateAndVisualizeHist(t[1],256,256,"Saturation");
	
		calculateAndVisualizeHist(t[2],256,256,"Value");
	}
	else if(flag==2)
	{
		cvtColor(src_image,temp,CV_BGR2YCrCb);
		split(temp,t);
		calculateAndVisualizeHist(t[0],256,256,"Y");
		
		calculateAndVisualizeHist(t[1],256,256,"Cr");
	
		calculateAndVisualizeHist(t[2],256,256,"Cb");
	}
	waitKey(0);
	destroyAllWindows();	
	return 0;
}

