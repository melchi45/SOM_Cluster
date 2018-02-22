// Pattern.h: interface for the Pattern class.
//
////////////////////////////////////////////////////////////////////////****************************************************************************
//  File Name	: Common.h
//	Purpose		: Input/Output Pattern Class
//  Creator		: Young ho Kim<melchi@nownuri.net>
//				  MFC Forum <http://stmail.chosun.ac.kr/~melchi/>
//****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <stdarg.h>

#ifndef _PATTERN_H_
#define _PATTERN_H_

class Pattern  
{
private:
	double *in_set;		// Pointer to input pattern array
	double *out_set;	// Pointer to output pattern array
	int id;				// Pattern Identification Number
	int in_size, out_size;	// Input and Output pattern sizes
public:		
	Pattern(int in, int out);
	Pattern(int in, int out, int data_id, ...);
	Pattern(int in, int out, int data_id, 
							double *in_array, double *out_array);
	Pattern(int in, int out, ifstream &infile);
	~Pattern(void);

	virtual inline double In(int id);
	virtual inline double Out(int id);

	virtual inline void Set_In(int id, double value);
	virtual inline void Set_Out(int id, double value);

	virtual inline int In_Size(void);
	virtual inline int Out_Size(void);
	virtual void Save(ofstream &outfile);
	virtual void Load(ifstream &infile);

	virtual void Print(void);
	virtual inline int Get_ID(void);

	virtual void Copy(Pattern &In);
};

Pattern::Pattern(int in, int out)
{
	in_size = in;
	out_size = out;
	in_set = new double[in_size];
	out_set = new double[out_size];
};

Pattern::~Pattern(void)
{
	if(in_set)
		delete[] in_set;
	if(out_set)
		delete[] out_set;
};
// Constructor using variable parameter list
Pattern::Pattern(int in, int out, int data_id, ...)
{
	in_size = in;
	out_size = out;
	in_set = new double[in_size];
	out_set = new double[out_size];

	id = data_id;
	va_list vl;

	va_start(vl, data_id);
	for(int i=0; i < in_size; i++)
	{
		in_set[i] = va_arg(vl, double);
	}

	for(int i=0; i< out_size ; i++)
	{
		out_set[i] = va_arg(vl, double);
	}

	va_end(vl);
};
// Define in/out size and initialize values using arrays
Pattern::Pattern(int in, int out, int data_id, 
				 double *in_array, double *out_array)
{  
	in_size = in;
	out_size = out;
	in_set = new double[in_size];
	out_set = new double[out_size];

	id = data_id;
	
	in_set = new double[in_size];
	for(int i=0; i < in_size; i++)
	{
		in_set[i] = in_array[i];
	}

	for(int i=0; i< out_size ; i++)
	{
		out_set[i] = out_array[i];
	}
};

Pattern::Pattern(int in, int out, ifstream &infile)
{   
	in_size = in;
	out_size = out;
	infile >> id;

	in_set = new double[in_size];
	out_set = new double[out_size];

	Load(infile);
};

double Pattern::In(int id)
{   
	return in_set[id];
};

double Pattern::Out(int id)
{   
	return out_set[id];
};

void Pattern::Set_In(int id, double value)
{   
	in_set[id] = value;
};

void Pattern::Set_Out(int id, double value)
{   
	out_set[id] = value;
};

int Pattern::In_Size(void)
{   
	return in_size;
};

int Pattern::Out_Size(void)
{   
	return out_size;
};

void Pattern::Save(ofstream &outfile)
{
	outfile << id << "\t";
	for(int i = 0; i< in_size; i++)
	{
		outfile << in_set[i] << "\t";
	}

	for(int i =0; i<out_size ; i++)
	{
		outfile << out_set[i] << "\t";
		if( i!=out_size-1)
			outfile << "\t";
	}
	outfile << endl;
};

void Pattern::Load(ifstream &infile)
{   
	for(int i=0; i< in_size; i++)
	{
		infile >> in_set[i];
	}

	for(int i=0 ; i < out_size; i++)
	{
		infile >> out_set[i];
	}

	char ch;
	ch = infile.peek();

	while(ch == '\n' || ch == EOF)
	{
		ch=infile.get();
		if(ch == EOF)
			break;
		ch=infile.peek();
	}
};

void Pattern::Print(void)
{  
	{
		cout << "ID : " << setw(4) 
			 << id << "  In : ";
	
		for(int i =0; i<in_size; i++)
			cout << in_set[i] 
				 << setw(9) << " ";
	}
	{
		cout << setw(2) 
			 << "Out : ";
	
		for(int i =0 ; i < out_size ; i++)
			cout << out_set[i] 
			     << setw(2) << " ";
	}

	cout << endl;
};

int Pattern::Get_ID(void)
{   
	return id;
};

void Pattern::Copy(Pattern &orig)
{
	int i;

	if(orig.In_Size() == in_size)
		for(i = 0 ; i < in_size; i++)
			in_set[i] = orig.In(i);
	
	if(orig.Out_Size() == out_size)
		for(i = 0 ; i < out_size; i++)
			out_set[i] = orig.Out(i);
};


#endif 
