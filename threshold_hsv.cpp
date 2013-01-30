#include"threshold_hsv.h"

int hl=160,hu=10;
int sl=150,su=255;
int vl=0,vu=255;
Mat src_image;

void thresh(int pos,void* x)
{
  Mat temp = Mat(src_image.cols,src_image.rows,CV_8U);
	Mat t[3];
	
	t[0] = Mat(src_image.cols,src_image.rows,CV_8U);
	t[1] = Mat(src_image.cols,src_image.rows,CV_8U);
	t[2] = Mat(src_image.cols,src_image.rows,CV_8U);
	
	cvtColor(src_image,temp,CV_BGR2HSV);
	if(hl>hu)
	{
		inRange(temp,Scalar(hu,0,0),Scalar(hl,255,255),t[0]);
		t[0] = 255 - t[0];
	}
	else
	{
		inRange(temp,Scalar(hl,0,0),Scalar(hu,255,255),t[0]);
	}
	
	if(sl>su)
	{
		inRange(temp,Scalar(0,su,0),Scalar(180,sl,255),t[1]);
		t[1] = 255 - t[1];
	}
	else
	{
		inRange(temp,Scalar(0,sl,0),Scalar(180,su,255),t[1]);
			
	}
	
	if(vl>vu)
	{
		inRange(temp,Scalar(0,0,vu),Scalar(180,255,vl),t[2]);
		t[2] = 255 - t[2];
	}
	else
	{
		inRange(temp,Scalar(0,0,vl),Scalar(180,255,vu),t[2]);
			
	}
	bitwise_and(t[0],t[1],t[1]);
	bitwise_and(t[1],t[2],t[2]);
	
	imshow("result",t[2]);
	
}

main(int argc,char** argv)
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
	
	resize(src,src_image,Size(800,600));
	namedWindow("morpho",1);
	
	imshow("original",src_image);
	
	createTrackbar( "HUE lower", "morpho" ,&hl,180,thresh );
	createTrackbar( "HUE upper", "morpho" ,&hu,180,thresh );
	createTrackbar( "Sat lower", "morpho" ,&sl,255,thresh );
	createTrackbar( "Sat upper", "morpho" ,&su,255,thresh );
	createTrackbar( "val lower", "morpho" ,&vl,255,thresh );
	createTrackbar( "val upper", "morpho" ,&vu,255,thresh );
	
	thresh(0,NULL);
	waitKey(0);
	
	
}
