#include "Kalman.h"
#include "math.h"


float Q=0.01;                                                               //系统过程噪声协方差
float R=0.01;                                                               //测量结果噪声协方差  越大每一次进行是变化越大

/*
第一个卡尔曼滤波为非实时的卡尔曼滤波 时间长【很长】

第二个卡尔曼滤波为实时卡尔曼滤波 时间段 用于PID控制
*/

float KalmanFilter (float Measure,float now_EV,float ProcessCovariance,float MeasureCovariance)//EVΪEstimateValue
{
	static float EstimateValue[2][2],KalmanGain;
	static float EstimateCovariance[2][2]={{1,0},{0,0}};
	
	EstimateValue[0][0] = now_EV;
	EstimateValue[0][1] = EstimateValue[0][0];
	EstimateCovariance[0][1] = EstimateCovariance[0][0]+ProcessCovariance;
	KalmanGain = EstimateCovariance[0][1]/(EstimateCovariance[0][1]+MeasureCovariance);
	EstimateValue[1][1] = EstimateValue[0][1]+KalmanGain*(Measure-EstimateValue[0][0]);
	EstimateCovariance[0][0] = (1-KalmanGain)*EstimateCovariance[0][1];
	
	
	
	return EstimateValue[1][1];
	
}

float Kalman(float Input)
{
	//变量定义
	static float optimal_value=1;											    //设置系统最优值初值
	static float deviation=1;													//设置系统偏差值初值
	float System_forecast=0;													//系统当前预测值定义
	float deviation_forecast=0;												    //系统当前误差值定义
	float Kalman_Gain=0;													    //卡尔曼增益定义
	//最优值计算
	System_forecast=optimal_value;																							//公式一
	deviation_forecast=deviation+Q; 																						//公式二
	Kalman_Gain=(deviation_forecast)/(deviation_forecast+R);										//公式四
	optimal_value=System_forecast+Kalman_Gain*(Input-System_forecast);					//公式三
	deviation=(1-Kalman_Gain)/deviation_forecast;																//公式五
	return optimal_value;																												//返回当次预测最优值
}
