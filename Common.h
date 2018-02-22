//****************************************************************************
//  File Name	: Common.h
//	Purpose		: This Header file contains some commonly used node types
//  Creator		: Young ho Kim<melchi@nownuri.net>
//				  MFC Forum <http://stmail.chosun.ac.kr/~melchi/>
//****************************************************************************

// define header file
#include "Base.h"

#ifndef _COMMON_H_
#define _COMMON_H_

// -------------------------------------------------------------------
// The Input Node class is a generic Input Node. 
// It can be used with most networks
//##ModelId=3A1160D602BE
class Input_Node : public Base_Node
{
public:
	// Default of one value set member (NODE_VALUE) and 
	// one error set member (NODE_ERROR)
	//##ModelId=3A1160D602D3
	Input_Node(int size = 1) : Base_Node(size, size)
	{
		for(int i = 0; i < size ; i++)
		{
			error[i] = 0.0;
			value[i] = 0.0;
		};
	};

	//##ModelId=3A1160D602DD
	virtual char *Get_Name(void)
	{
		static char name[]="Input Node";
		return name;
	};
};

// -------------------------------------------------------------------
// The Bias Node class id a node that alaways proceduces the same output.
// The Bias Node's default output.
//##ModelId=3A1160D60304
class Bias_Node : public Input_Node
{
public:
	//##ModelId=3A1160D60322
	Bias_Node( double bias = 1.0) : Input_Node(1)
	{	
		value[0] = bias;
	};

	//##ModelId=3A1160D6032C
	virtual void Set_Value(double value, int id=0)
	{
	};

	//##ModelId=3A1160D60338
	virtual double Get_Value(int id = 0)
	{
		return value[0];
	};
	
	//##ModelId=3A1160D6034A
	virtual char *Get_Name(void)
	{
		static char name[]="BIAS_NODE";
		return name;
	};

};

#endif
