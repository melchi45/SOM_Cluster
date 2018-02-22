//****************************************************************************
//  File Name	: EpochBP.h
//	Purpose		: Epoch BackPropagation Neural Network Class
//  Creator		: Young ho Kim<melchi@nownuri.net>
//				  MFC Forum <http://stmail.chosun.ac.kr/~melchi/>
//****************************************************************************

#ifndef _EPOCH_H_
#define _EPOCH_H_

#include "Base.h"
#include "Common.h"
#include "BackProp.h"

#define EPOCH 2

//##ModelId=3A1160D6023C
class Epoch_BP_Link : public BP_Link
{
public:
	//##ModelId=3A1160D6025B
	Epoch_BP_Link( int size=3); // Default of three value set members
								// (WEIGHT, DELTA, EPOCH)
	//##ModelId=3A1160D6026F
	virtual char *Get_Name(void);
	//##ModelId=3A1160D60283
	virtual void Update_Weight(double new_val);
	//##ModelId=3A1160D60296
	virtual void Epoch(int mode);
};

//##ModelId=3A1160D6025B
Epoch_BP_Link::Epoch_BP_Link(int size) : BP_Link(size)
{
	value[WEIGHT] = Random(-1.0, 1.0);
};

//##ModelId=3A1160D60283
void Epoch_BP_Link::Update_Weight(double new_val)
{
	value[EPOCH] += new_val;
};

//##ModelId=3A1160D60296
void Epoch_BP_Link::Epoch(int mode)
{
	double momentum = Out_Node()->Get_Value(MOMENTUM);
	double delta = value[EPOCH]/mode;
	value[WEIGHT] += delta + (momentum * value[DELTA]);	
	value[DELTA] = delta;
	value[EPOCH] =0.0;
};

//##ModelId=3A1160D6026F
char *Epoch_BP_Link::Get_Name(void)
{
	static char name[] = "EPOCH_BP_LINK";
	return name;
};


#endif // !defined(AFX_EPOCHBP_H__255571C2_81F7_4409_AF7B_C362BE3E1AAA__INCLUDED_)
