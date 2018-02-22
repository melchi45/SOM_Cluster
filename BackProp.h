//****************************************************************************
//  File Name	: BackProp.h
//	Purpose		: BackPropagation Neural Network Class
//  Creator		: Young ho Kim<melchi@nownuri.net>
//				  MFC Forum <http://stmail.chosun.ac.kr/~melchi/>
//****************************************************************************

#ifndef _BACK_PROPAGATION_H_
#define _BACK_PROPAGATION_H_

#include "base.h"
#include "common.h"
#include "adaline.h"

#define DELTA 1
#define MOMENTUM 2

//##ModelId=3A1160DD001F
class BP_Node : public Feed_Forward_Node
{
protected:
	//##ModelId=3A1160DD0034
	virtual double Transfer_Function(double value);
public:
	//##ModelId=3A1160DD0048
	BP_Node(int v_size =1, int e_size=0); // Default of 1 value set member (NODE_VALUE)
	//##ModelId=3A1160DD005B
	virtual char *Get_Name(void);
};

//##ModelId=3A1160DD00AB
class BP_Link : public Base_Link
{
public:
	//##ModelId=3A1160DD00C9
	BP_Link(int size = 2); // default of 2 of 1 link value set members(WEIGHT, DELTA)
	//##ModelId=3A1160DD00D3
	virtual void Save( ofstream &outfile);
	//##ModelId=3A1160DD00DE
	virtual void Load( ifstream &infile);
	//##ModelId=3A1160DD00F1
	virtual char *Get_Name(void);
	//##ModelId=3A1160DD0105
	virtual void Update_Weight(double new_val);
};

//##ModelId=3A1160DD014B
class BP_Output_Node : public BP_Node
{
public:
	//##ModelId=3A1160DD016B
	BP_Output_Node( double lr, double mt, int v_size=3, int e_size=1);
	//default of 3 value set members (NODE_VALUE, LEARNING_RATE, MOMENTUM)
	//default of 1 error set member (NODE_ERROR)
protected:
	//##ModelId=3A1160DD0188
	virtual double Compute_Error(int mode=0);
	//##ModelId=3A1160DD019C
	virtual void Learn(int mode=0);
	//##ModelId=3A1160DD01B0
	virtual char *Get_Name(void);
};

//##ModelId=3A1160DD020A
class BP_Hidden_Node : public BP_Output_Node
{
public:
	//##ModelId=3A1160DD0229
	BP_Hidden_Node(double lr, double mt, int v_size=3, int e_size=1);
	//default of 3 value set members (NODE_VALUE, LEARNING_RATE, MOMENTUM)
	//default of 1 error set member (NODE_ERROR)
	//##ModelId=3A1160DD0246
	virtual char *Get_Name(void);
protected:
	//##ModelId=3A1160DD025A
	virtual double Compute_Error(int mode=0);
};

//##ModelId=3A1160DD0034
double BP_Node::Transfer_Function(double value)
{
	return 1.0 / (1.0 + exp(-value));	// Sigmoid function
};

//##ModelId=3A1160DD0048
BP_Node::BP_Node(int v_size, int e_size) : Feed_Forward_Node(v_size, e_size)
{
};

//##ModelId=3A1160DD005B
char *BP_Node::Get_Name(void)
{
	static char name[] = "BP_NODE";
	return name;
};

//##ModelId=3A1160DD00C9
BP_Link::BP_Link( int size) : Base_Link(size)
{
	value[WEIGHT] = Random(-1.0, 1.0);	// weight random value between -1.0 and 1.0
	value[DELTA] = 0.0;					// Initialize previous change to 0.0
};

//##ModelId=3A1160DD00D3
void BP_Link::Save( ofstream &outfile)
{
	outfile << setw(4) << id << " " << setprecision(18)
		<< value[WEIGHT] << " " << setw(4)
		<< In_Node()->Get_ID() << " "
		<< setw(4) << Out_Node()->Get_ID() << endl;
};

//##ModelId=3A1160DD00DE
void BP_Link::Load( ifstream &infile)
{
	infile >> id;
	infile >> value[WEIGHT];
	int dummy;
	infile >> dummy;
	infile >> dummy;
};

//##ModelId=3A1160DD00F1
char *BP_Link::Get_Name(void)
{
	static char name[] = "BP_LINK";
	return name;
};

//##ModelId=3A1160DD0105
void BP_Link::Update_Weight(double new_val)
{
	double momentum = Out_Node()->Get_Value(MOMENTUM);
	value[WEIGHT] += new_val + (momentum * value[DELTA]);

	value[DELTA] = new_val;
};

//##ModelId=3A1160DD016B
BP_Output_Node::BP_Output_Node(double lr, double mt, int v_size, int e_size) : BP_Node(v_size, e_size)
{
	value[LEARNING_RATE] = lr;
	value[MOMENTUM] = mt;
};

//##ModelId=3A1160DD0188
double BP_Output_Node::Compute_Error(int mode)
{
	return value[NODE_VALUE] * (1.0-value[NODE_VALUE]) * (error[NODE_ERROR] - value[NODE_ERROR]);
};

//##ModelId=3A1160DD019C
void BP_Output_Node::Learn(int mode)
{
	double delta;
	error[NODE_ERROR] = Compute_Error();

	in_links.Reset_To_Head();
	Base_Link *link;
	int cnt = in_links.Count();

	for(int i = 0; i < cnt; i++)
	{
		link = in_links.Curr();
		delta = value[LEARNING_RATE] * error[NODE_ERROR] * link->In_Value(); // Delta Rule
		link->Update_Weight(delta);
		in_links.Next();
	}
};

//##ModelId=3A1160DD01B0
char *BP_Output_Node::Get_Name(void)
{
	static char name[] = "BP_OUTPUT_NODE";
	return name;
};

//##ModelId=3A1160DD0229
BP_Hidden_Node::BP_Hidden_Node(double lr, double mt, int v_size, int e_size) : BP_Output_Node(lr, mt, v_size, e_size)
{
};

//##ModelId=3A1160DD0246
char *BP_Hidden_Node::Get_Name(void)
{
	static char name[] = " BP_HIDDEN_NODE";
	return name;
};

//##ModelId=3A1160DD025A
double BP_Hidden_Node::Compute_Error(int mode)
{
	double total =0;
	out_links.Reset_To_Head();
	int cnt=out_links.Count();

	for(int i = 0; i<cnt; i++)
	{
		total += out_links.Curr()->Weighted_Out_Error();
		out_links.Next();
	}
	return value[NODE_VALUE] * (1.0 - value[NODE_VALUE]) * total;
};

//##ModelId=3A1160DE007B
class BackProp_Network : public ADALINE_Network
{
protected:
	//##ModelId=3A1160DE0099
	int num_layers;
	//##ModelId=3A1160DE00AD
	int first_hidden_node;
	//##ModelId=3A1160DE00C1
	int first_output_node;
	//##ModelId=3A1160DE00DF
	int *node_cnt;
	//##ModelId=3A1160DE00F3
	double momentum_term;

	//##ModelId=3A1160DE0111
	virtual void Create_Network(void);

public:
	//##ModelId=3A1160DE0125
	BackProp_Network(char filename[]);
	//##ModelId=3A1160DE012F
	BackProp_Network(double lr, double mt, int layers, ...);
	//##ModelId=3A1160DE0144
	BackProp_Network(double lr, double mt, int layers, int nodes[]);
	//##ModelId=3A1160DE0158
	BackProp_Network(void);
	//##ModelId=3A1160DE0162
	~BackProp_Network(void);

	//##ModelId=3A1160DE0175
	virtual double Get_Error(int id=0);
	//##ModelId=3A1160DE0180
	virtual void Set_Error(double new_val, int id=0);
	//##ModelId=3A1160DE0194
	virtual void Set_Error(Pattern *output_pattern);
	//##ModelId=3A1160DE01A7
	virtual double Get_Value(int id=0);
	//##ModelId=3A1160DE01B2
	virtual void Save(ofstream &outfile);
	//##ModelId=3A1160DE01C5
	virtual void Load(ifstream &infile);
	//##ModelId=3A1160DE01CF
	virtual void Run(int mode =0);
	//##ModelId=3A1160DE01DB
	virtual void Learn(int mode=0);
	//##ModelId=3A1160DE01ED
	virtual char *Get_Name(void);
	//##ModelId=3A1160DE020C
	virtual int Get_Num_Layers(void);
	//##ModelId=3A1160DE021F
	virtual int Get_Layer_Count(int id);
};

//##ModelId=3A1160DE0111
void BackProp_Network::Create_Network(void)
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
			node[curr++] = new BP_Hidden_Node(learning_rate, momentum_term);
		}
	}

	first_output_node = curr;

	for(i =0; i < node_cnt[num_layers-1] ; i++)
	{
		node[curr++] = new BP_Output_Node(learning_rate, momentum_term);
	}

	for( i=0; i< num_links; i++)
	{
		link[i] = new BP_Link;
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

//##ModelId=3A1160DE0125
BackProp_Network::BackProp_Network(char filename[]) : ADALINE_Network()
{
	ifstream infile(filename);
	node_cnt = NULL;
	Load(infile);
	infile.close();
};

//##ModelId=3A1160DE012F
BackProp_Network::BackProp_Network(double lr, double mt, int layers, ...) : ADALINE_Network()
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

	Create_Network();
};

//##ModelId=3A1160DE0144
BackProp_Network::BackProp_Network(double lr, double mt, int layers, int nodes[]) : ADALINE_Network()
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

	Create_Network();
};

//##ModelId=3A1160DE0158
BackProp_Network::BackProp_Network(void) : ADALINE_Network()
{ 
	node_cnt = NULL;
};

//##ModelId=3A1160DE0162
BackProp_Network::~BackProp_Network(void)
{ 
	if(node_cnt) 
		delete []node_cnt;
};

//##ModelId=3A1160DE0175
double BackProp_Network::Get_Error(int id)
{ 
	return node[id + first_output_node]->Get_Error(); // in output layer only with next index 0
};

//##ModelId=3A1160DE0180
void BackProp_Network::Set_Error(double new_val, int id)
{   
	node[id + first_output_node]->Set_Error(new_val); // Set error in output layer only starting with index 0
};

//##ModelId=3A1160DE0194
void BackProp_Network::Set_Error(Pattern *output_pattern)
{   
	for(int i=0; i < node_cnt[num_layers-1] ; i++)
		node[i + first_output_node]->Set_Error(output_pattern->Out(i));
};

//##ModelId=3A1160DE01A7
double BackProp_Network::Get_Value(int id)
{   
	return node[id+first_output_node]->Get_Value();
};

//##ModelId=3A1160DE01B2
void BackProp_Network::Save(ofstream &outfile)
{   
	outfile << id << endl;
	outfile << num_layers << endl;
	for(int i =0; i<num_layers; i++)
		outfile << node_cnt[i] << endl;

	Save_Nodes_Links(outfile);
};

//##ModelId=3A1160DE01C5
void BackProp_Network::Load(ifstream &infile)
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

//##ModelId=3A1160DE01CF
void BackProp_Network::Run(int mode)
{ 
	Load_Inputs();
	for(int i = first_hidden_node; i < num_nodes; i++)
		node[i]->Run();
};

//##ModelId=3A1160DE01DB
void BackProp_Network::Learn(int mode)
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

//##ModelId=3A1160DE01ED
char *BackProp_Network::Get_Name(void)
{ 
	static char name[] = "BACKPROPAGATION_NETWORK";
	return name;
};

//##ModelId=3A1160DE020C
int BackProp_Network::Get_Num_Layers(void)
{ 
	return num_layers;
};

//##ModelId=3A1160DE021F
int BackProp_Network::Get_Layer_Count(int id)
{ 
	return node_cnt[id];
};

#endif 
