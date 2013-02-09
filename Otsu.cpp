#include"common.h"

int getOtsuThreshold(Mat hist,int bins)
{
	float q1=0,q2=0,u1=0,u2=0,w1=0,w2=0,norm,maxVal=0,Val;
	int t = 1,index=-1;
	
	for(int i=0;i<bins;i++)
	{
		norm+= hist.at<float>(i);
		w2+= i*hist.at<float>(i);
	}
	w2/=norm;
	
	while(t<bins)
	{
		q1+=hist.at<float>(t)/norm;
		
		if(q1==0)
			continue; 
		
		q2 = 1 - q1;
		w1+=(t*(hist.at<float>(t)/norm));
		u1 = w1/q1;
		w2-=(t*(hist.at<float>(t)/norm));
		u2 = w2/q2;
		
		Val = q1 * q2 * pow((u1-u2),2);
		
		if(Val > maxVal)
		{
			maxVal = Val;
			index = t;
		}
		
		t++;
	}
	return index;	
}
