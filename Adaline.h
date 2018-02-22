//****************************************************************************
//  File Name	: ADALINE_Node.h
//	Purpose		: This headrt file contains the ADALINE_Node classes
//  Creator		: Young ho Kim<melchi@nownuri.net>
//				  MFC Forum <http://stmail.chosun.ac.kr/~melchi/>
//****************************************************************************
#ifndef _ADALINE_H_
#define _ADALINE_H_

#include "Base.h"
#include "Common.h"
#include "Pattern.h"

//##ModelId=3A1160DE028D
class ADALINE_Node : public Feed_Forward_Node
{
protected:
	//##ModelId=3A1160DE02AC
	virtual double Transfer_Function(double value);
public:
	//##ModelId=3A1160DE02C9
	ADALINE_Node();
	//##ModelId=3A1160DE02D4
	ADALINE_Node(double lr);
	//##ModelId=3A1160DE02DE
	virtual void Learn(int mode);
	//##ModelId=3A1160DE02E9
	virtual char *Get_Name(void);
};
//******************************************************************
// Constructor
//##ModelId=3A1160DE02C9
ADALINE_Node::ADALINE_Node() 
	: Feed_Forward_Node(2/*v_size*/ ,1/*e_size*/)
{
};
//******************************************************************
// Constructor with Learning Rate specified
//##ModelId=3A1160DE02D4
ADALINE_Node::ADALINE_Node(double lr) 
	: Feed_Forward_Node(2/*v_size*/ ,1/*e_size*/)
{
	value[LEARNING_RATE] = lr;
};

//******************************************************************
// Threshold Transfer Function 
// if x < 0 f(x) = -1.0
// else		f(x) = 1.0
//##ModelId=3A1160DE02AC
double ADALINE_Node::Transfer_Function(double value)
{
	if(value < 0)
		return -1.0;
	else
		return 1.0;
};

//##ModelId=3A1160DE02DE
void ADALINE_Node::Learn(int mode)
{
	error[NODE_ERROR] = value[NODE_VALUE] * -2.0; // Compute error
	Base_Link *link;			// create link
	in_links.Reset_To_Head();	// link initialize
	int cnt = in_links.Count(); // link count number
	double delta;				

	for(int i = 0; i < cnt ; i++)  // Traverse Input links
	{
		link = in_links.Curr();
		delta = value[LEARNING_RATE] * link->In_Value() * error[NODE_ERROR]; // Delta Rule
		link->Update_Weight(delta); // new weight
		in_links.Next();
	}
};

//##ModelId=3A1160DE02E9
char *ADALINE_Node::Get_Name(void)
{
	static char name[] = "ADALINE_NODE";
	return name;
};

//##ModelId=3A1160DE0356
class ADALINE_Link : public Base_Link // Link for ADALINE Node
{
public:
	//##ModelId=3A1160DE0375
	ADALINE_Link(void);
	//##ModelId=3A1160DE0388
	virtual void Save( ofstream &outfile);
	//##ModelId=3A1160DE0392
	virtual void Load( ifstream &infile);
	//##ModelId=3A1160DE039D
	virtual char *Get_Name(void);
};
//******************************************************************
// Automatically initialized weight value to random number
// Small random values are usually used
//##ModelId=3A1160DE0375
ADALINE_Link::ADALINE_Link(void) : Base_Link()
{
	value[WEIGHT] = Random(-1.0, 1.0);
};

//##ModelId=3A1160DE0388
void ADALINE_Link::Save( ofstream &outfile)
{
	outfile << setw(4) << id << " " << setprecision(18)
		<< value[WEIGHT] << " " << setw(4) << In_Node()->Get_ID() << " "
		<< setw(4) << Out_Node()->Get_ID() << endl;
};

//##ModelId=3A1160DE0392
void ADALINE_Link::Load( ifstream &infile)
{
	infile >> id;
	infile >> value[WEIGHT];

	int dummy;

	infile >> dummy;	// Skip In node IDs
	infile >> dummy;	// Skip Out node IDs
};

//##ModelId=3A1160DE039D
char *ADALINE_Link::Get_Name(void)
{
	static char name[] = "ADALINE_LINK";
	return name;
};

//##ModelId=3A1160DF00AE
class ADALINE_Network : public Base_Network // ADALINE Network Node
{
protected:
	//##ModelId=3A1160DF00D6
	virtual void Create_Network(void);
	//##ModelId=3A1160DF00E1
	virtual void Load_Inputs(void);
	//##ModelId=3A1160DF00F5
	double learning_rate;
public:
	//##ModelId=3A1160DF0112
	ADALINE_Network(char filename[] );
	//##ModelId=3A1160DF011D
	ADALINE_Network(int size);
	//##ModelId=3A1160DF0127
	ADALINE_Network(int size, double lr);
	//##ModelId=3A1160DF013A
	ADALINE_Network(void);
	//##ModelId=3A1160DF0144
	virtual double Get_Value(int id = 0);
	//##ModelId=3A1160DF014F
	virtual void Set_Value(double new_val, int id=0);
	//##ModelId=3A1160DF0163
	virtual void Set_Value(Pattern *input_pattern);
	//##ModelId=3A1160DF0176
	virtual void Save(ofstream &outfile);
	//##ModelId=3A1160DF0181
	virtual void Load(ifstream &infile);
	//##ModelId=3A1160DF0194
	virtual void Run(int mode=0);
	//##ModelId=3A1160DF01A0
	virtual void Learn(int mode=0);
	//##ModelId=3A1160DF01B3
	virtual char *Get_Name(void);
};

//##ModelId=3A1160DF00D6
void ADALINE_Network::Create_Network(void)
{ 
	node = new Base_Node*[num_nodes];
	link = new Base_Link*[num_links];

	for(int i=0; i < num_nodes-2; i++) // Create input Nodes
		node[i] = new Input_Node;

	node[num_nodes-2] = new Bias_Node;	// Create Bias Node

	node[num_nodes-1] = new ADALINE_Node(learning_rate);	// Create ADALINE

	for(int i = 0; i < num_links; i++)		// Create links
		link[i] = new ADALINE_Link;

	for(int i = 0; i < num_links; i++)			// Connect inputs to ADALINE
		Connect(node[i], node[num_nodes-1], link[i]);
};

//##ModelId=3A1160DF00E1
void ADALINE_Network::Load_Inputs(void)
{   
	int cnt = in_links.Count();	// If network node has any input links.

	if(cnt >0)			// load the connected node's input values into the input layer
	{				
		in_links.Reset_To_Head();		// For all in links connected to Network node

		for(int i =0; i <cnt; i++)
		{
			Set_Value(in_links.Curr()->In_Value(), i);
			in_links.Next();
		}
	}
};

//##ModelId=3A1160DF0112
ADALINE_Network::ADALINE_Network(char filename[] ) : Base_Network()	// Constructor
{   
	ifstream infile(filename);
	Load(infile);
	infile.close();
};

//##ModelId=3A1160DF011D
ADALINE_Network::ADALINE_Network(int size)
{   
	num_nodes = size +2;	// num nodes equals input layer
							// size +bias + ADALINE Node
	num_links = size +1;	// num links equal on for each input
							// layer node and on for bias node
	learning_rate = 0;
	Create_Network();
};

//##ModelId=3A1160DF0127
ADALINE_Network::ADALINE_Network(int size, double lr) : Base_Network()
{   
	num_nodes = size + 2;
	num_links = size + 1;
	learning_rate = lr;
	Create_Network();
};

//##ModelId=3A1160DF013A
ADALINE_Network::ADALINE_Network(void) : Base_Network()
{   
};

//##ModelId=3A1160DF0144
double ADALINE_Network::Get_Value(int id)
{ 
	return node[num_nodes -1]->Get_Value();	// return only ADALINE node value 
											// id defaults to 0
};

//##ModelId=3A1160DF014F
void ADALINE_Network::Set_Value(double new_val, int id)
{   
	node[id]->Set_Value(new_val);
};

//##ModelId=3A1160DF0163
void ADALINE_Network::Set_Value(Pattern *input_pattern)
{ 
	for(int i =0; i < input_pattern->In_Size() ;  i++)	// Load pattern's input
		node[i]->Set_Value(input_pattern->In(i));		// valur into input layer
};

//##ModelId=3A1160DF0176
void ADALINE_Network::Save(ofstream &outfile)
{ 
	outfile << id << endl;
	Save_Nodes_Links(outfile);
};

//##ModelId=3A1160DF0181
void ADALINE_Network::Load(ifstream &infile)
{ 
	infile >> id;
	Load_Nodes_Links(infile);
};

//##ModelId=3A1160DF0194
void ADALINE_Network::Run(int mode)
{   
	Load_Inputs();
	node[num_nodes-1]->Run();	// Run ADALINE node only
};

//##ModelId=3A1160DF01A0
void ADALINE_Network::Learn(int mode)
{   
	node[num_nodes-1]->Learn();	// only ADALINE node needs to excute its Learn
};

//##ModelId=3A1160DF01B3
char *ADALINE_Network::Get_Name(void)
{ 
	static char name[]="ADALINE_Network";
	return name;
};
#endif //_ADALINE_H_
