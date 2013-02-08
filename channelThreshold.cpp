#include"common.h"

int channel1_lower=125,channel1_upper=175;
int channel2_lower=150,channel2_upper=255;
int channel3_lower=150,channel3_upper=255;
int flag=0;				//Flag for Color space selection
Mat src_image;			//Global Image Variable

/** Function used for finding the image region which satisfies the bounds on its values in the three channels described by parameters. It is cyclic in nature.
	- Parameters : Lower and upper bound for each channel of the image (3 channel - 8 bit image)
	- Flag can be passed as command line argument for choosing modes among {0(RGB), 1(HSV), 2(YCrCb)}. Default is RGB  
*/	

void channelThreshold(int pos,void* x)
{
  Mat temp = Mat(src_image.cols,src_image.rows,CV_8U);
	Mat t[3];
	
	t[0] = Mat(src_image.cols,src_image.rows,CV_8U);
	t[1] = Mat(src_image.cols,src_image.rows,CV_8U);
	t[2] = Mat(src_image.cols,src_image.rows,CV_8U);
	
	if(flag==1)
		cvtColor(src_image,temp,CV_BGR2HSV);
    else if(flag==2)
		cvtColor(src_image,temp,CV_BGR2YCrCb);	
	else if(flag!=1&&flag!=2)
		src_image.copyTo(temp);
		
	split(temp,t);
			
	if(channel1_lower>channel1_upper)
	{
		inRange(temp,Scalar(channel1_upper,0,0),Scalar(channel1_lower,255,255),t[0]);
		t[0] = 255 - t[0];
	}
	else
	{
		inRange(temp,Scalar(channel1_lower,0,0),Scalar(channel1_upper,255,255),t[0]);
	}
	
	if(channel2_lower>channel2_upper)
	{
		inRange(temp,Scalar(0,channel2_upper,0),Scalar(180,channel2_lower,255),t[1]);
		t[1] = 255 - t[1];
	}
	else
	{
		inRange(temp,Scalar(0,channel2_lower,0),Scalar(180,channel2_upper,255),t[1]);
			
	}
	
	if(channel3_lower>channel3_upper)
	{
		inRange(temp,Scalar(0,0,channel3_upper),Scalar(180,255,channel3_lower),t[2]);
		t[2] = 255 - t[2];
	}
	else
	{
		inRange(temp,Scalar(0,0,channel3_lower),Scalar(180,255,channel3_upper),t[2]);
			
	}
	bitwise_and(t[0],t[1],t[1]);
	bitwise_and(t[1],t[2],t[2]);
	
	imshow("Result",t[2]);
	
}
/* Main function as an example of usage... Modify it according to requirements. Will try to make it more modular*/
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
	
	
	if(argc>=3)
	{
		flag = atoi(argv[2]);
	}
	if(src.cols>800||src.rows>600)
		resize(src,src_image,Size(800,600));
	else
		src.copyTo(src_image);
	
	namedWindow("InRange",1);
	
	imshow("Original",src_image);
	if(flag==1)
	{
		createTrackbar( "Channel1 lower", "InRange" ,&channel1_lower,180,channelThreshold );
		createTrackbar( "Channel1 upper", "InRange" ,&channel1_upper,180,channelThreshold );
	}
	else
	{
		createTrackbar( "Channel1 lower", "InRange" ,&channel1_lower,255,channelThreshold );
		createTrackbar( "Channel1 upper", "InRange" ,&channel1_upper,255,channelThreshold );
	}
	createTrackbar( "Channel2 lower", "InRange" ,&channel2_lower,255,channelThreshold );
	createTrackbar( "Channel2 upper", "InRange" ,&channel2_upper,255,channelThreshold );
	createTrackbar( "Channel3 lower", "InRange" ,&channel3_lower,255,channelThreshold );
	createTrackbar( "Channel3 upper", "InRange" ,&channel3_upper,255,channelThreshold );
	
	channelThreshold(0,NULL);
	waitKey(0);
	destroyAllWindows();
	
}
