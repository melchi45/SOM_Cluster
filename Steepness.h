//****************************************************************************
//  File Name	: Steepness.h
//	Purpose		: Steepnessagation Neural Network Class
//  Creator		: Young ho Kim<melchi@nownuri.net>
//				  MFC Forum <http://stmail.chosun.ac.kr/~melchi/>
//****************************************************************************

#ifndef _STEEPNESS_H_
#define _STEEPNESS_H_

#include "base.h"
#include "common.h"
#include "BackProp.h"

//##ModelId=3A1160D002D4
class Steepness_Node : public BP_Node
{
protected:
	//##ModelId=3A1160D002F1
	virtual double Transfer_Function(double value);
public:
	//##ModelId=3A1160D00310
	Steepness_Node(int v_size =1, int e_size=0); // Default of 1 value set member (NODE_VALUE)
	//##ModelId=3A1160D00323
	virtual char *Get_Name(void);
};

//##ModelId=3A1160D00388
class Steepness_Link : public BP_Link
{
public:
	//##ModelId=3A1160D0039D
	Steepness_Link(int size = 2); // default of 2 of 1 link value set members(WEIGHT, DELTA)
	//##ModelId=3A1160D003B0
	virtual void Save( ofstream &outfile);
	//##ModelId=3A1160D003C4
	virtual void Load( ifstream &infile);
	//##ModelId=3A1160D003D8
	virtual char *Get_Name(void);
	//##ModelId=3A1160D003E3
	virtual void Update_Weight(double new_val);
	//##ModelId=3A1160D1000E
	virtual void Update_Beta(double new_val);
};

//##ModelId=3A1160D10054
class Steepness_Output_Node : public Steepness_Node
{
public:
	//##ModelId=3A1160D10072
	Steepness_Output_Node( double lr, double mt, double beta, int v_size=3, int e_size=1);
	//default of 3 value set members (NODE_VALUE, LEARNING_RATE, MOMENTUM)
	//default of 1 error set member (NODE_ERROR)
protected:
	//##ModelId=3A1160D10090
	virtual double Compute_Error(int mode=0);
	//##ModelId=3A1160D100A5
	virtual void Learn(int mode=0);
	//##ModelId=3A1160D100B8
	virtual char *Get_Name(void);
};

//##ModelId=3A1160D10126
class Steepness_Hidden_Node : public BP_Hidden_Node
{
public:
	//##ModelId=3A1160D1013B
	Steepness_Hidden_Node(double lr, double mt, double beta, int v_size=3, int e_size=1);
	//default of 3 value set members (NODE_VALUE, LEARNING_RATE, MOMENTUM, BETA)
	//default of 1 error set member (NODE_ERROR)
	//##ModelId=3A1160D1016C
	virtual char *Get_Name(void);
protected:
	//##ModelId=3A1160D10176
	virtual double Compute_Error(int mode=0);
};

//##ModelId=3A1160D002F1
double Steepness_Node::Transfer_Function(double value)
{
	return 1.0 / (1.0 + exp(-value));	// Sigmoid function
};

//##ModelId=3A1160D00310
Steepness_Node::Steepness_Node(int v_size, int e_size) : BP_Node(v_size, e_size)
{
};

//##ModelId=3A1160D00323
char *Steepness_Node::Get_Name(void)
{
	static char name[] = "Steepness_NODE";
	return name;
};

//##ModelId=3A1160D0039D
Steepness_Link::Steepness_Link( int size) : BP_Link(size)
{
	value[WEIGHT] = Random(-1.0, 1.0);	// weight random value between -1.0 and 1.0
	value[DELTA] = 0.0;					// Initialize previous change to 0.0
	value[BETA] = Random(0.1, 4.0);	
};

//##ModelId=3A1160D003B0
void Steepness_Link::Save( ofstream &outfile)
{
	outfile << setw(4) << id << " " << setprecision(18)
		<< value[WEIGHT] << " " << setw(4)
		<< value[BETA] << " " << setw(4)
		<< In_Node()->Get_ID() << " "
		<< setw(4) << Out_Node()->Get_ID() << endl;
};

//##ModelId=3A1160D003C4
void Steepness_Link::Load( ifstream &infile)
{
	infile >> id;
	infile >> value[WEIGHT];
	infile >> value[BETA];
	int dummy;
	infile >> dummy;
	infile >> dummy;
};

//##ModelId=3A1160D003D8
char *Steepness_Link::Get_Name(void)
{
	static char name[] = "Steepness_LINK";
	return name;
};

//##ModelId=3A1160D003E3
void Steepness_Link::Update_Weight(double new_val)
{
	double momentum = Out_Node()->Get_Value(MOMENTUM);
	value[WEIGHT] += new_val + (momentum * value[DELTA]);

	value[DELTA] = new_val;
};

//##ModelId=3A1160D1000E
void Steepness_Link::Update_Beta(double new_val)
{
	value[BETA] += new_val;
};


//##ModelId=3A1160D10072
Steepness_Output_Node::Steepness_Output_Node(double lr, double mt, double beta, int v_size, int e_size) : Steepness_Node(v_size, e_size)
{
	value[LEARNING_RATE] = lr;
	value[MOMENTUM] = mt;
	value[BETA] = beta;
};

//##ModelId=3A1160D10090
double Steepness_Output_Node::Compute_Error(int mode)
{
	return value[NODE_VALUE] * (1.0-value[NODE_VALUE]) * (error[NODE_ERROR] - value[NODE_ERROR]) * value[BETA];
};

//##ModelId=3A1160D100A5
void Steepness_Output_Node::Learn(int mode)
{
	double delta;
	double beta;
	error[NODE_ERROR] = Compute_Error();

	in_links.Reset_To_Head();
	Base_Link *link;
	int cnt = in_links.Count();

	for(int i = 0; i < cnt; i++)
	{
		link = in_links.Curr();
		delta = value[LEARNING_RATE] * error[NODE_ERROR] * link->In_Value(); // Delta Rule
		beta = (value[LEARNING_RATE] * error[NODE_ERROR] * link->In_Value()) / value[BETA]; // Delta Rule
		link->Update_Weight(delta);
		link->Update_Beta(beta);
		in_links.Next();
	}
};

//##ModelId=3A1160D100B8
char *Steepness_Output_Node::Get_Name(void)
{
	static char name[] = "Steepness_OUTPUT_NODE";
	return name;
};

//##ModelId=3A1160D1013B
Steepness_Hidden_Node::Steepness_Hidden_Node(double lr, double mt, double beta, int v_size, int e_size) : BP_Hidden_Node(lr, mt, v_size, e_size)
{
};

//##ModelId=3A1160D1016C
char *Steepness_Hidden_Node::Get_Name(void)
{
	static char name[] = " Steepness_HIDDEN_NODE";
	return name;
};

//##ModelId=3A1160D10176
double Steepness_Hidden_Node::Compute_Error(int mode)
{
	double total =0;
	out_links.Reset_To_Head();
	int cnt=out_links.Count();

	for(int i = 0; i<cnt; i++)
	{
		total += out_links.Curr()->Weighted_Out_Error();
		out_links.Next();
	}
	return value[NODE_VALUE] * (1.0 - value[NODE_VALUE]) * total * value[BETA];
};

//##ModelId=3A1160D20308
class Steepness_Network : public BackProp_Network
{
protected:
	//##ModelId=3A1160D20326
	int num_layers;
	//##ModelId=3A1160D3001B
	int first_hidden_node;
	//##ModelId=3A1160D3002F
	int first_output_node;
	//##ModelId=3A1160D30057
	int *node_cnt;
	//##ModelId=3A1160D30075
	double momentum_term;
	//##ModelId=3A1160D30089
	double beta;

	//##ModelId=3A1160D3009D
	virtual void Create_Network(void);

public:
	//##ModelId=3A1160D300B1
	Steepness_Network(char filename[]);
	//##ModelId=3A1160D300BB
	Steepness_Network(double lr, double mt, double beta, int layers, ...);
	//##ModelId=3A1160D300E3
	Steepness_Network(double lr, double mt, double beta, int layers, int nodes[]);
	//##ModelId=3A1160D30102
	Steepness_Network(void);
	//##ModelId=3A1160D3010C
	~Steepness_Network(void);

	//##ModelId=3A1160D30129
	virtual double Get_Error(int id=0);
	//##ModelId=3A1160D30135
	virtual void Set_Error(double new_val, int id=0);
	//##ModelId=3A1160D30148
	virtual void Set_Error(Pattern *output_pattern);
	//##ModelId=3A1160D3015B
	virtual double Get_Value(int id=0);
	//##ModelId=3A1160D30179
	virtual void Save(ofstream &outfile);
	//##ModelId=3A1160D30184
	virtual void Load(ifstream &infile);
	//##ModelId=3A1160D30197
	virtual void Run(int mode =0);
	//##ModelId=3A1160D301A1
	virtual void Learn(int mode=0);
	//##ModelId=3A1160D301AD
	virtual char *Get_Name(void);
	//##ModelId=3A1160D301BF
	virtual int Get_Num_Layers(void);
	//##ModelId=3A1160D301CA
	virtual int Get_Layer_Count(int id);
};

//##ModelId=3A1160D3009D
void Steepness_Network::Create_Network(void)
{
	node = new Base_Node*[num_nodes];
	link = new Base_Link*[num_links];

	int curr = 0;

	for( int i=0; i < node_cnt[0]; i++)
	{
		node[curr++] = new Input_Node;
	}

	first_hidden_node = curr;

	for(i = 1; i < num_layers-1 ; i++)
	{
		for(int j=0; j < node_cnt[i]; j++)
		{
			node[curr++] = new Steepness_Hidden_Node(learning_rate, momentum_term, beta);
		}
	}

	first_output_node = curr;

	for(i =0; i < node_cnt[num_layers-1] ; i++)
	{
		node[curr++] = new Steepness_Output_Node(learning_rate, momentum_term, beta);
	}

	for( i=0; i< num_links; i++)
	{
		link[i] = new Steepness_Link;
		if(link[i] == NULL)
			cout << "Error - Fail to allocate link" << i << endl;
	}

	curr = 0;
	int layer1 =0, layer2=first_hidden_node;
	
	for(i = 0; i<num_layers-1; i++)
	{
		for(int j = 0; j < node_cnt[i+1]; j++)
		for(int k = 0; k < node_cnt[i]; k++)
			Connect(node[layer1+k], node[layer2+j], link[curr++]);
		layer1 = layer2;
		layer2 += node_cnt[i+1];
		
	}
};

//##ModelId=3A1160D300B1
Steepness_Network::Steepness_Network(char filename[]) : BackProp_Network()
{
	ifstream infile(filename);
	node_cnt = NULL;
	Load(infile);
	infile.close();
};

//##ModelId=3A1160D300BB
Steepness_Network::Steepness_Network(double lr, double mt, double b, int layers, ...) : BackProp_Network()
{ 
	num_nodes = 0;
	num_links = 0;

	num_layers = layers;
	va_list vl;

	va_start(vl, layers);
	node_cnt = new int[layers];

	for(int i = 0; i< layers; i++)
	{
		node_cnt[i] = va_arg(vl, int);
		num_nodes += node_cnt[i];
		if(i > 0)
		{
			num_links += node_cnt[i-1] * node_cnt[i]; // link between layers
		}
	}

	va_end(vl);

	learning_rate = lr;
	momentum_term = mt;
	beta = b;

	Create_Network();
};

//##ModelId=3A1160D300E3
Steepness_Network::Steepness_Network(double lr, double mt, double b, int layers, int nodes[]) : BackProp_Network()
{ 
	num_nodes=0;
	num_links=0;

	num_layers = layers;
	node_cnt = new int[layers];

	for(int i = 0; i < layers;  i++)
	{
		node_cnt[i] = nodes[i];
		num_nodes += node_cnt[i];

		if( i > 0)
			num_links += node_cnt[i-1] * node_cnt[i]; // link between layers
	}

	learning_rate = lr;
	momentum_term = mt;
	beta = b;

	Create_Network();
};

//##ModelId=3A1160D30102
Steepness_Network::Steepness_Network(void) : BackProp_Network()
{ 
	node_cnt = NULL;
};

//##ModelId=3A1160D3010C
Steepness_Network::~Steepness_Network(void)
{ 
	if(node_cnt) 
		delete []node_cnt;
};

//##ModelId=3A1160D30129
double Steepness_Network::Get_Error(int id)
{ 
	return node[id + first_output_node]->Get_Error(); // in output layer only with next index 0
};

//##ModelId=3A1160D30135
void Steepness_Network::Set_Error(double new_val, int id)
{   
	node[id + first_output_node]->Set_Error(new_val); // Set error in output layer only starting with index 0
};

//##ModelId=3A1160D30148
void Steepness_Network::Set_Error(Pattern *output_pattern)
{   
	for(int i=0; i < node_cnt[num_layers-1] ; i++)
		node[i + first_output_node]->Set_Error(output_pattern->Out(i));
};

//##ModelId=3A1160D3015B
double Steepness_Network::Get_Value(int id)
{   
	return node[id+first_output_node]->Get_Value();
};

//##ModelId=3A1160D30179
void Steepness_Network::Save(ofstream &outfile)
{   
	outfile << id << endl;
	outfile << num_layers << endl;
	for(int i =0; i<num_layers; i++)
		outfile << node_cnt[i] << endl;

	Save_Nodes_Links(outfile);
};

//##ModelId=3A1160D30184
void Steepness_Network::Load(ifstream &infile)
{ 
	infile >> id;
	infile >> num_layers;
	if(node_cnt)
		delete []node_cnt;
	node_cnt = new int[num_layers];

	for(int i = 0; i < num_layers; i++)
		infile >> node_cnt[i];
	
	Load_Nodes_Links(infile);
};

//##ModelId=3A1160D30197
void Steepness_Network::Run(int mode)
{ 
	Load_Inputs();
	for(int i = first_hidden_node; i < num_nodes; i++)
		node[i]->Run();
};

//##ModelId=3A1160D301A1
void Steepness_Network::Learn(int mode)
{   
	int cnt = out_links.Count();
	if(cnt > 0)
	{
		out_links.Reset_To_Head();
		for(int i =0; i < cnt; i++)
		{
			node[i+first_output_node]->Set_Error(out_links.Curr()->Out_Error());
			out_links.Next();
		}
	}
	for(int i = num_nodes-1; i >= first_hidden_node; i--)
		node[i]->Learn();
};

//##ModelId=3A1160D301AD
char *Steepness_Network::Get_Name(void)
{ 
	static char name[] = "SteepnessAGATION_NETWORK";
	return name;
};

//##ModelId=3A1160D301BF
int Steepness_Network::Get_Num_Layers(void)
{ 
	return num_layers;
};

//##ModelId=3A1160D301CA
int Steepness_Network::Get_Layer_Count(int id)
{ 
	return node_cnt[id];
};

#endif 
