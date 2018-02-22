//****************************************************************************
//  File Name	: Son.h
//	Purpose		: This header file contains the SON classes
//  Creator		: Young ho Kim<melchi@nownuri.net>
//				  MFC Forum <http://stmail.chosun.ac.kr/~melchi/>
//****************************************************************************
#ifndef _SON_H_
#define _SON_H_

#include "Adaline.h"
#include "Common.h"

//****************************************************************************

#define COMPOSITE	0
#define	ROW			1
#define COL			2

//****************************************************************************
//##ModelId=3A1160D3030A
class SON_Node : public Base_Node // SON processing Node
{
public:
	//##ModelId=3A1160D30329
	SON_Node(int v_size = 2, int e_size = 0);	// Default of 2 value set members
												// (NODE_VALUE, LEARNING_RATE)
	//##ModelId=3A1160D3033C
	SON_Node(float lr);
	//##ModelId=3A1160D30346
	void Set_Learning_Rate(double new_lr);
	//##ModelId=3A1160D30351
	virtual void Run(int mode = 0);
	//##ModelId=3A1160D3035C
	virtual void Learn(int mode);
	//##ModelId=3A1160D303AA
	virtual char *Get_Name(void);
	//##ModelId=3A1160D303B5
	virtual void Print(ofstream &out);
};
//****************************************************************************
//##ModelId=3A1160D40008
class SON_Link : public ADALINE_Link
{
public:
	//##ModelId=3A1160D4003A
	SON_Link(void);
	//##ModelId=3A1160D40044
	virtual char *Get_Name(void);
};
//****************************************************************************
// Constructor
//##ModelId=3A1160D30329
SON_Node::SON_Node(int v_size, int e_size) : Base_Node(v_size, e_size)
{
};
//****************************************************************************
// Constructor
//##ModelId=3A1160D3033C
SON_Node::SON_Node(float lr) : Base_Node(2, 0) // contructor with Learning Rate specified
{
	value[LEARNING_RATE] = lr;
};
//****************************************************************************
//##ModelId=3A1160D303B5
void SON_Node::Print(ofstream &out)
{
	in_links.Reset_To_Head();
	Base_Link *link;
	int cnt = in_links.Count();
	for(int i = 0; i < cnt; i++)
	{
		link = in_links.Curr();
		out << link->Get_Value() << " ";
		in_links.Next();
	}
	out << endl;
};
//****************************************************************************
//##ModelId=3A1160D30351
void SON_Node::Run(int mode)
{
	in_links.Reset_To_Head();
	double total = 0;
	Base_Link *link;
	int cnt = in_links.Count();
	for(int i = 0; i < cnt ; i++)
	{
		link = in_links.Curr();
		total += pow( link->In_Value() - link->Get_Value(WEIGHT), 2);
		in_links.Next();
	}
	value[NODE_VALUE] = sqrt(total);
};
//****************************************************************************
//##ModelId=3A1160D3035C
void SON_Node::Learn(int mode)
{
	Base_Link *link;
	in_links.Reset_To_Head();
	int cnt = in_links.Count();
	double delta;
	for(int i = 0; i < cnt ; i++)
	{
		link = in_links.Curr();
		delta = value[LEARNING_RATE] * (link->In_Value() - link->Get_Value(WEIGHT));
		link->Update_Weight(delta);
		in_links.Next();
	}
};
//****************************************************************************
//##ModelId=3A1160D303AA
char *SON_Node::Get_Name( void)
{
	static char name[] = "SON_NODE";
	return name;
};
//****************************************************************************
//##ModelId=3A1160D4003A
SON_Link::SON_Link(void) : ADALINE_Link() // Contructor
{
	value[WEIGHT] = Random(0.0, 1.0);
};
//****************************************************************************
//##ModelId=3A1160D40044
char *SON_Link::Get_Name(void)
{
	static char name[] = "SON_LINK";
	return name;
};

//##ModelId=3A1160D401DF
class SON_Network : public ADALINE_Network
{
public:
	int x_size, y_size;									// size of Kohonen layer
protected:
	double init_learning_rate, final_learning_rate;		// LEarning Rate range
	int init_neigh_size, neigh_decrement_interval;
	//##ModelId=3A1160D40207
	int neighborhood;									// Neig. Size info
	//##ModelId=3A1160D4021B
	long num_iterations;								// number of tarning iterations
	//##ModelId=3A1160D4022F
	long iteration;										// current iteration
	//##ModelId=3A1160D4024D
	double learning_rate;								// current learning rate
	//##ModelId=3A1160D4029D
	int neigh_size;										// current neighborhood size
	int min_x, min_y;									// current winning node position
	//##ModelId=3A1160D40384
	Base_Node	***K_node;								// Kohonen layer

	//##ModelId=3A1160D403A1
	virtual	void Create_Network(void);

public:
	//##ModelId=3A1160D403CA
	SON_Network(char filename[]);
	//##ModelId=3A1160D5000A
	SON_Network(int num_input, int x_dim, int y_dim, double init_lr,
		double final_lr, int init_ns, int ns_dec_int, long iterations);
	//##ModelId=3A1160D50064
	SON_Network(void);
	//##ModelId=3A1160D5006F
	~SON_Network(void);

	//##ModelId=3A1160D5008D
	virtual void Epoch(int code = 0);
	//##ModelId=3A1160D500A0
	virtual double Get_Error(int id = 0);
	//##ModelId=3A1160D500D2
	virtual void Set_Error(double new_val, int id = 0);
	//##ModelId=3A1160D500F0
	virtual double Get_Value(int id = 0);
	//##ModelId=3A1160D50104
	virtual void Save(ofstream &outfile);
	//##ModelId=3A1160D50118
	virtual void Load(ifstream &infile);
	//##ModelId=3A1160D50123
	virtual void Run(int mode = 0);
	//##ModelId=3A1160D50136
	virtual void Learn(int mode = 0);
	//##ModelId=3A1160D5014A
	virtual char *Get_Name(void);
	//##ModelId=3A1160D50155
	virtual void Print(ofstream &out);
	//##ModelId=3A1160D50168
	virtual int Get_Neighborhood_Size(void);
	//##ModelId=3A1160D5017C
	virtual double Get_Learning_Rate(void);
	//##ModelId=3A1160D50190
	virtual int Get_Input_Count(void);
	//##ModelId=3A1160D5019B
	virtual int Get_Rows(void);
	//##ModelId=3A1160D501AE
	virtual int Get_Cols(void);
};

//##ModelId=3A1160D50155
void SON_Network::Print(ofstream &out)
{
	for(int x = 0; x < x_size; x++)
		for(int y = 0; y < y_size ; y++)
		{
			out << x << " " << y << "   ";
			K_node[x][y]->Print(out);
		}
};

//##ModelId=3A1160D403A1
void SON_Network::Create_Network(void)
{
	node = new Base_Node*[num_nodes];
	num_links = num_nodes * x_size * y_size;

	K_node = new Base_Node**[x_size];

	for(int x = 0; x < x_size ; x++)
	{
		K_node[x] = new Base_Node*[y_size];
	}

	link = new Base_Link*[num_links];

	for(int i = 0; i < num_nodes; i++)
		node[i] = new Input_Node;

	int curr = 0;

	for(int x =0; x < x_size; x++)
	{
		for(int y = 0; y < y_size; y++)
		{
			K_node[x][y] = new SON_Node;
			for(int i =0; i < num_nodes; i++)
			{
				link[curr] = new SON_Link;
				Connect(node[i], K_node[x][y], link[curr++]);
			}
		}
	}
};

//##ModelId=3A1160D403CA
SON_Network::SON_Network(char filename[]) : ADALINE_Network()
{
	ifstream infile(filename);
	Load(infile);
	infile.close();
};

//##ModelId=3A1160D5000A
SON_Network::SON_Network(int num_inputs, int x_dim, int y_dim, double init_lr,
						double final_lr, int init_ns, int ns_dec_int, long iterations) : ADALINE_Network()
{
	init_learning_rate = init_lr;
	final_learning_rate = final_lr;
	learning_rate = init_lr;
	init_neigh_size = init_ns;
	neigh_decrement_interval = ns_dec_int;
	num_iterations = iterations;
	iteration = 0;
	num_nodes = num_inputs;
	neighborhood = init_neigh_size;
	x_size = x_dim;
	y_size = y_dim;
	Create_Network();
};

//##ModelId=3A1160D50064
SON_Network::SON_Network(void) : ADALINE_Network()
{
	num_nodes = 0;
	num_links = 0;
};

//##ModelId=3A1160D5006F
SON_Network::~SON_Network()
{
	for(int x = 0; x < x_size; x++)
	{
		for(int y = 0; y < y_size; y++)
		{
			delete K_node[x][y];
		}
	}
	
	for(int x = 0; x < x_size; x++)
		delete []K_node[x];
	
	if(K_node)
		delete []K_node;
}

//##ModelId=3A1160D500A0
double SON_Network::Get_Error(int id)
{
	return 0;
};

//##ModelId=3A1160D500F0
double SON_Network::Get_Value(int id)
{
	switch(id)
	{
	case ROW:
		return min_x;
	case COL:
		return min_y;
	default:
	case COMPOSITE:
		return min_x * min_y * y_size + min_y;
	}
};

//##ModelId=3A1160D50104
void SON_Network::Save(ofstream &outfile)
{
	outfile << id << endl;

	outfile << init_learning_rate << endl;
	outfile << final_learning_rate << endl;
	outfile << init_neigh_size << endl;
	outfile << neigh_decrement_interval << endl;
	outfile << num_iterations << endl;
	outfile << x_size << endl;
	outfile << y_size << endl;

	Save_Nodes_Links(outfile);

	for(int x = 0; x < x_size; x++)
	{
		for(int y = 0; y < y_size ; y++)
		{
			K_node[x][y]->Save(outfile);
		}
	}
};

//##ModelId=3A1160D50118
void SON_Network::Load(ifstream &infile)
{
	infile >> id;

	infile >> init_learning_rate;
	infile >> final_learning_rate;
	infile >> init_neigh_size;
	infile >> neigh_decrement_interval;
	infile >> num_iterations;
	infile >> x_size;
	infile >> y_size;

	Load_Nodes_Links(infile);

	for(int x = 0; x < x_size; x++)
	{
		for( int y = 0; y < y_size ; y++)
		{
			K_node[x][y]->Load(infile);
		}
	}
};

//##ModelId=3A1160D50123
void SON_Network::Run(int mode)
{
	double min_value = 99999.0;
	double node_value;

	Load_Inputs();

	for(int x = 0; x < x_size; x++)
	{
		for(int y = 0; y < y_size; y++)
		{
			K_node[x][y]->Run();
			node_value = K_node[x][y]->Get_Value(NODE_VALUE);
			if(node_value < min_value)
			{
				min_value = node_value;
				min_x = x;
				min_y = y;
			}
		}
	}
};

//##ModelId=3A1160D50136
void SON_Network::Learn(int mode)
{
	int x_start = min_x - neighborhood;
	int x_stop = min_x + neighborhood;
	int y_start = min_y - neighborhood;
	int y_stop = min_y + neighborhood;

	if(x_start < 0)
		x_start = 0;
	if(x_stop >= x_size) 
		x_stop = x_size - 1;
	if(y_start < 0)
		y_start = 0;
	if(y_stop >= y_size)
		y_stop = y_size - 1;

	for(int x = x_start; x <= x_stop; x++)
	{
		for(int y = y_start; y <= y_stop; y++)
		{
			K_node[x][y]->Set_Value(learning_rate, LEARNING_RATE);
			K_node[x][y]->Learn();
		}
	}
};

//##ModelId=3A1160D5014A
char *SON_Network::Get_Name(void)
{
	static char name[] = "SON_NETWORK";
	return name;
};

//##ModelId=3A1160D5008D
void SON_Network::Epoch(int code)
{
	iteration++;

	learning_rate = init_learning_rate - 
		(((double)iteration / (double) num_iterations ) * (init_learning_rate - final_learning_rate));

	if((iteration + 1) % neigh_decrement_interval == 0 && neighborhood > 0)
		neighborhood--;
};

//##ModelId=3A1160D50168
int SON_Network::Get_Neighborhood_Size(void)
{
	return neighborhood;
};

//##ModelId=3A1160D5017C
double SON_Network::Get_Learning_Rate(void)
{
	return learning_rate;
};

//##ModelId=3A1160D50190
int SON_Network::Get_Input_Count(void)
{
	return num_nodes;
};

//##ModelId=3A1160D5019B
int SON_Network::Get_Rows(void) 
{
	return x_size;
};

//##ModelId=3A1160D501AE
int SON_Network::Get_Cols(void)
{
	return y_size;
};

//##ModelId=3A1160D500D2
void SON_Network::Set_Error(double new_val, int id)
{
};

#endif //_SON_H_
