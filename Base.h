//****************************************************************************
//  File Name	: Base.h
//	Purpose		: This Header file contains th base classes for Neural 
//				  Network nodes and links from linked list.
//  Creator		: Young ho Kim<melchi@nownuri.net>
//				  MFC Forum <http://stmail.chosun.ac.kr/~melchi/>
//****************************************************************************

// Define Header File
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// Define Header file Name
#ifndef _BASE_H_
#define _BASE_H_

// Initialize value
#define NODE_VALUE 0
#define LEARNING_RATE 1
#define NODE_ERROR 0
#define WEIGHT 0
#define BETA 1

class Base_Node;	//Foward declaration to links can use the base node type
//##ModelId=3A1160D80194
class Base_Link  
{
private:
	//##ModelId=3A1160D801B2
	static int ticket;

protected:
	//##ModelId=3A1160D801C6
	int id;					// ID number form link
	//##ModelId=3A1160D801E5
	double *value;			// Value(s) for link
	//##ModelId=3A1160D8020E
	Base_Node *in_node;		// Node instance link is comming from
	//##ModelId=3A1160D8022C
	Base_Node *out_node;	// Node instance link is going to
	//##ModelId=3A1160D80253
	int value_size;			// Number of Node instance link

public:
	//##ModelId=3A1160D80267
	Base_Link( int size=1);	// Constructor
	//##ModelId=3A1160D8027B
	~Base_Link(void);		// Destructor

	//##ModelId=3A1160D8028F
	virtual void Save( ofstream &outfile );		// Save to Outfile
	//##ModelId=3A1160D8029A
	virtual void Load( ifstream &infile );		// Load to Infile
	//##ModelId=3A1160D802B7
	inline virtual double Get_Value(int id=WEIGHT);	
	//##ModelId=3A1160D802C1
	inline virtual void Set_Value(double new_val, int id=WEIGHT);
	//##ModelId=3A1160D802DF
	inline virtual void Set_In_Node(Base_Node *node, int id);
	//##ModelId=3A1160D802FD
	inline virtual void Set_Out_Node(Base_Node *node, int id);
	//##ModelId=3A1160D8031B
	inline virtual Base_Node *In_Node(void);
	//##ModelId=3A1160D8032F
	inline virtual Base_Node *Out_Node(void);
	//##ModelId=3A1160D80339
	inline virtual char *Get_Name(void);
	//##ModelId=3A1160D8034D
	inline virtual void Update_Weight(double new_val);
	//##ModelId=3A1160D80361
	inline virtual void Update_Beta(double new_val);
	//##ModelId=3A1160D80375
	inline int Get_ID(void);
	//##ModelId=3A1160D80389
	inline virtual double In_Value(int mode=NODE_VALUE);
	//##ModelId=3A1160D80394
	inline virtual double Out_Value(int mode=NODE_VALUE);
	//##ModelId=3A1160D803A7
	inline virtual double In_Error(int mode=NODE_ERROR);
	//##ModelId=3A1160D803BB
	inline virtual double Out_Error(int mode=NODE_ERROR);
	//##ModelId=3A1160D803CF
	inline virtual double Weighted_In_Value(int mode=NODE_VALUE);
	//##ModelId=3A1160D90005
	inline virtual double Weighted_Out_Value(int mode=NODE_VALUE);
	//##ModelId=3A1160D90019
	inline virtual double Weighted_In_Error(int mode=NODE_VALUE);
	//##ModelId=3A1160D9002D
	inline virtual double Weighted_Out_Error(int mode=NODE_VALUE);
	//##ModelId=3A1160D90041
	inline virtual int Get_Set_Size(void);
	//##ModelId=3A1160D90055
	inline virtual void Epoch(int mode=0);
};

//##ModelId=3A1160D9025E
class LList  
{
private:
	//##ModelId=3A1160D90395
	struct NODE
	{
		NODE *next, *prev;
		//##ModelId=3A1160D903B4
		Base_Link *element;
	};

	NODE *head, *tail, *curr;
	//##ModelId=3A1160D90272
	int count;

public:
	//##ModelId=3A1160D90290
	LList(void);
	//##ModelId=3A1160D9029B
	~LList(void);

	//##ModelId=3A1160D902AE
	int Add_To_Tail(Base_Link *element);
	//##ModelId=3A1160D902B8
	int Add_Node(Base_Link *element);
	//##ModelId=3A1160D902CC
	int Del_Node(void);
	//##ModelId=3A1160D902E0
	int Del(Base_Link *element);
	//##ModelId=3A1160D902EA
	int Find(Base_Link *element);
	//##ModelId=3A1160D902F5
	inline void Clear(void);
	//##ModelId=3A1160D90308
	inline int Count(void);
	//##ModelId=3A1160D90312
	inline void Reset_To_Head(void);
	//##ModelId=3A1160D9031D
	inline void Reset_To_Tail(void);
	//##ModelId=3A1160D90330
	inline Base_Link *Curr(void);
	//##ModelId=3A1160D9033B
	inline void Next(void);
	//##ModelId=3A1160D9034E
	inline void Prev(void);
};

//##ModelId=3A1160D90041
int Base_Link::Get_Set_Size(void)
{
	return value_size;
};

//##ModelId=3A1160D80267
Base_Link::Base_Link(int size)		// Constructor
{
	id=++ticket;
	value_size = size;
	if(value_size <= 0) 
		value = NULL;
	else
		value = new double[value_size];

	for(int i=0 ; i < value_size; i++)	// initilize value set to zero
	{
		value[i] = 0.0;
	}
	in_node = out_node = NULL;
};

//##ModelId=3A1160D8027B
Base_Link::~Base_Link(void) // Destructor for Base Links
{
	if(value_size > 0)
		delete[] value;
};

//##ModelId=3A1160D8028F
void Base_Link::Save( ofstream &outfile)
{
	outfile << id << endl;
	outfile << value_size;		// Store value set

	if(value)
		delete []value;
	value = new double[value_size];
	for(int i=0; i<value_size; i++)
		outfile << " " << setprecision(18) << value[i];

	outfile << endl;
};

//##ModelId=3A1160D8029A
void Base_Link::Load(ifstream &infile)
{
	infile >> id;
	infile >> value_size;
	
	if(value)
		delete []value;
	value=new double[value_size];	// Load value set

	for(int i=0; i < value_size ; i++)
		infile >> value[i];
};

//##ModelId=3A1160D802B7
double Base_Link::Get_Value(int id)
{
	return value[id];
};

//##ModelId=3A1160D802C1
void Base_Link::Set_Value(double new_val, int id)
{
	value[id] = new_val;
};

//##ModelId=3A1160D802DF
void Base_Link::Set_In_Node(Base_Node *node, int id)
{
	in_node = node;
};

//##ModelId=3A1160D802FD
void Base_Link::Set_Out_Node(Base_Node *node, int id)
{
	out_node = node;
};

//##ModelId=3A1160D8031B
Base_Node *Base_Link::In_Node(void)
{
	return in_node;
};

//##ModelId=3A1160D8032F
Base_Node *Base_Link::Out_Node(void)
{
	return out_node;
};

//##ModelId=3A1160D80339
char *Base_Link::Get_Name(void)
{
	static char name[]="BASE_LINK";
	return name;
};

//##ModelId=3A1160D8034D
void Base_Link::Update_Weight(double new_val)
{
	value[WEIGHT] += new_val;
};

//##ModelId=3A1160D80361
void Base_Link::Update_Beta(double new_val)
{
};

//##ModelId=3A1160D80375
int Base_Link::Get_ID(void)
{
	return id;
};

//##ModelId=3A1160D90055
void Base_Link::Epoch(int code)
{
};

//##ModelId=3A1160D801B2
int Base_Link::ticket=-1;		// This static variable is shared by all
								// links derived from the base link class. Its
								// purpose is to give each link created from
								// the base_link class a unique identification
								// number

//##ModelId=3A1160DA0396
class Base_Node					//Base Neural-Network Node
{ 
private:
	//##ModelId=3A1160DA03AA
	static int ticket;
protected:
	//##ModelId=3A1160DA03BE
	int id;					// identification Number
	//##ModelId=3A1160DA03DC
	double *value;			// Value(s) stored by this node
	//##ModelId=3A1160DB0012
	int value_size;			// Number of Values stored by this node
	//##ModelId=3A1160DB0026
	double *error;			// Error value(s) stored by this node
	//##ModelId=3A1160DB003A
	int error_size;			// Number of Error values stored by this node

	//##ModelId=3A1160DB0076
	LList in_links;			// List for input links
	//##ModelId=3A1160DB009F
	LList out_links;		// List from output links

public:
	//##ModelId=3A1160DB00C6
	Base_Node(int v_size=1, int e_size=1);	// Constructor
	//##ModelId=3A1160DB00E4
	~Base_Node(void);						// Destructor

	//##ModelId=3A1160DB00F9
	LList *In_Links(void);
	//##ModelId=3A1160DB010D
	LList *Out_Links(void);

	//##ModelId=3A1160DB0117
	virtual void Run(int mode=0);
	//##ModelId=3A1160DB0135
	virtual void Learn(int mode=0);
	//##ModelId=3A1160DB013F
	virtual void Epoch(int code=0);
	//##ModelId=3A1160DB0153
	virtual void Load( ifstream &infile);
	//##ModelId=3A1160DB0167
	virtual void Save( ofstream &outfile);

	//##ModelId=3A1160DB017B
	inline virtual double Get_Value(int id=NODE_VALUE);
	//##ModelId=3A1160DB018F
	inline virtual void Set_Value(double new_val, int id=NODE_VALUE);
	//##ModelId=3A1160DB01AD
	inline virtual double Get_Error(int id=NODE_ERROR);
	//##ModelId=3A1160DB01C1
	inline virtual void Set_Error(double new_val, int id=NODE_ERROR);
	//##ModelId=3A1160DB01DF
	inline int Get_ID(void);
	//##ModelId=3A1160DB01E9
	inline virtual char *Get_Name(void);
	//##ModelId=3A1160DB01FD
	void Create_Link_To(Base_Node &to_node, Base_Link *link);
	//##ModelId=3A1160DB021B
	virtual void Print(ofstream &out);
	
	// Connection and Disconnect function
	//##ModelId=3A1160DB0225
	friend void Connect(Base_Node &from_node, Base_Node &to_node, Base_Link *link);
	//##ModelId=3A1160DB024D
	friend void Connect(Base_Node &from_node, Base_Node &to_node, Base_Link &link);
	//##ModelId=3A1160DB0275
	friend void Connect(Base_Node *from_node, Base_Node *to_node, Base_Link *link);
	//##ModelId=3A1160DB0293
	friend int DisConnect(Base_Node *from_node, Base_Node *to_node);

	//##ModelId=3A1160DB02B1
	friend double Random(double lower_bound, double upper_bound);
};

//##ModelId=3A1160DB00C6
Base_Node::Base_Node(int v_size, int e_size)	// Constructor
{
	id=++ticket;
	if(v_size <= 0)			// Create value storage
	{
		value_size=0;
		value = NULL;
	}
	else
	{
		value_size = v_size;
		value = new double[v_size];
	}

	for (int i=0; i < v_size ; i++)
	{
		value[i] = 0.0;
	}

	if(e_size <= 0)		// Create error storage
	{
		error_size=0; 
		error = NULL;
	}
	else
	{
		error_size = e_size;
		error=new double[e_size];
	}

	for(int i=0; i< e_size; i++)		//set all errors to zero
		error[i] = 0.0;
};

//##ModelId=3A1160DB00E4
Base_Node::~Base_Node(void)			// Destuctor
{
	if(value_size > 0) delete[] value;
	if(error_size > 0) delete[] error;
};

//##ModelId=3A1160DB00F9
LList *Base_Node::In_Links(void)
{  
	return &in_links;
};

//##ModelId=3A1160DB010D
LList *Base_Node::Out_Links(void)
{    
	return &out_links;
};

//##ModelId=3A1160DB0117
void Base_Node::Run(int mode)
{    
};

//##ModelId=3A1160DB0135
void Base_Node::Learn(int mode)
{   
};

//##ModelId=3A1160DB013F
void Base_Node::Epoch(int code)
{    
};

//##ModelId=3A1160DB0153
void Base_Node::Load( ifstream &infile)
{
    infile >> id;
	infile >> value_size;
	if(value)
		delete []value;
	value = new double[value_size];		// Load value set

	for(int i = 0; i < value_size ; i++)
		infile >> value[i];
	infile >> error_size;

	if(error) delete []error;
	error = new double[error_size];		// Load error set

	for(int i = 0;i < error_size; i++)
		infile >> error[i];
};

//##ModelId=3A1160DB0167
void Base_Node::Save( ofstream &outfile)
{    
	outfile << setw(4) << id << endl;
	outfile << value_size;			// store value set

	for( int i=0; i < value_size; i++)
		outfile <<  " " << setprecision(18) << value[i];
	
	outfile << endl;
	outfile << error_size;			// store error set

	for(int i =0 ; i < error_size ; i++)
		outfile << " " << setprecision(18) << error[i];
	outfile << endl;
};

//##ModelId=3A1160DB017B
double Base_Node::Get_Value(int id)
{
    return value[id];
};

//##ModelId=3A1160DB018F
void Base_Node::Set_Value(double new_val, int id)
{
    value[id] = new_val;
};

//##ModelId=3A1160DB01AD
double Base_Node::Get_Error(int id)
{
    return error[id];
};

//##ModelId=3A1160DB01C1
void Base_Node::Set_Error(double new_val, int id)
{
    error[id] = new_val;
};

//##ModelId=3A1160DB01DF
int Base_Node::Get_ID(void)
{
    return id;
};

//##ModelId=3A1160DB01E9
char *Base_Node::Get_Name(void)
{
    static char name[] = "BASE_NODE";
	return name;
};

//##ModelId=3A1160DB01FD
void Base_Node::Create_Link_To(Base_Node &to_node, Base_Link *link) // Create Link from Link to Node
{
    out_links.Add_To_Tail(link);
	to_node.In_Links()->Add_To_Tail(link);
	link->Set_In_Node(this, id);
	link->Set_Out_Node(&to_node, to_node.Get_ID());
};

// Make Connection From Node1 to Node2 with Pointer Link
void Connect(Base_Node &from_node, Base_Node &to_node, Base_Link *link)
{   
	from_node.Create_Link_To(to_node, link);
};
// Make Connection From Node1 to Node2 with Link
void Connect(Base_Node &from_node, Base_Node &to_node, Base_Link &link)
{
    from_node.Create_Link_To(to_node, &link);
};
// Make Connection From Pointer Node1 to Pointer Node2 with Pointer Link
void Connect(Base_Node *from_node, Base_Node *to_node, Base_Link *link)
{    
	from_node->Create_Link_To(*to_node, link);
};
// Disconnection link from Node1 to Node2
int DisConnect(Base_Node *from_node, Base_Node *to_node)
{   
	LList *out_links = from_node->Out_Links();
	int flag = 0;
	out_links->Reset_To_Head();

	for( int i = 0; i < out_links->Count(); i++)	// for each output link
	{
		if(out_links->Curr()->Out_Node() == to_node)
		{
			flag =1;
			break;
		}
		out_links->Next();
	}

	if(flag == 1)	// link exists, delete it from both nodes
	{
		out_links->Curr()->Out_Node()->In_Links()->Del(out_links->Curr());
		out_links->Del_Node();
		return 1;
	}
	else
		return 0;		// link not found
};

double Random(double lower_bound, double upper_bound)	// Generate Random Number
{
	return ( (double)( ( rand()%RAND_MAX) )/(double)RAND_MAX) * 
		(upper_bound - lower_bound) + lower_bound;
};
// Save Outfile
//##ModelId=3A1160DB021B
void Base_Node::Print( ofstream &out)
{ 
	out << "Node ID : " << id << "     Node Name: " << Get_Name() << endl;
	out << "Value Set : ";
	for( int i=0; i< value_size; i++)
		out << value[i] << " ";

	out << endl;
	out << "Error Set: ";

	for(int i = 0; i < error_size ; i++)
		out << error[i] << " ";
	out << endl;

	in_links.Reset_To_Head();

	for(int i = 0 ; i < in_links.Count(); i++)
	{
		out << "In Link ID : " << in_links.Curr()->Get_ID() << " "
			<< "Link Name : " << in_links.Curr()->Get_Name() << " "
			<< "Source Node : " << in_links.Curr()->In_Node()->Get_ID() << " "
			<< "Value Set : ";
		
		for(int j=0; j < in_links.Curr()->Get_Set_Size(); j++)
			out << in_links.Curr()->Get_Value(j) << " ";
		out << endl;
		in_links.Next();
	}

	out_links.Reset_To_Head();
	for(int i = 0; i < out_links.Count(); i++)
	{
		out << "Out Link ID : " << out_links.Curr()->Get_ID() << " "
			<< "Link Name : " << out_links.Curr()->Get_Name() << " "
			<< "Dest Node : " << out_links.Curr()->Out_Node()->Get_ID() << " "
			<< "Value Set : ";

		for(int j=0; j < out_links.Curr()->Get_Set_Size(); j++)
			out << out_links.Curr()->Get_Value(j) << " ";
		out << endl;
		out_links.Next();
	}
	out << endl;
};
// This static variable id shared by all
// links derived from the base link class. Its
// purpose is to give each link created from
// the base_link class a unique identification
// number
//##ModelId=3A1160DA03AA
int Base_Node::ticket=-1;

//##ModelId=3A1160D80389
double Base_Link::In_Value(int mode)	// These Base_Link members
{		
	return in_node->Get_Value(mode);	// must be defined after the
};

//##ModelId=3A1160D80394
double Base_Link::Out_Value(int mode)	// Base_Node class because
{
	return out_node->Get_Value(mode);	// they reference specific
};

//##ModelId=3A1160D803A7
double Base_Link::In_Error(int mode)	// Base_Node Members.
{
	return in_node->Get_Error(mode);
};

//##ModelId=3A1160D803BB
double Base_Link::Out_Error(int mode)
{
	return out_node->Get_Error(mode);
};

//##ModelId=3A1160D803CF
double Base_Link::Weighted_In_Value(int mode)
{
	return in_node->Get_Value(mode)*value[WEIGHT];
};

//##ModelId=3A1160D90005
double Base_Link::Weighted_Out_Value(int mode)
{
	return out_node->Get_Value(mode)*value[WEIGHT];
};

//##ModelId=3A1160D90019
double Base_Link::Weighted_In_Error(int mode)
{
	return in_node->Get_Error(mode)*value[WEIGHT];
};

//##ModelId=3A1160D9002D
double Base_Link::Weighted_Out_Error(int mode)
{
	return out_node->Get_Error(mode)*value[WEIGHT];
};

// This derived class provides
// a generic feed-forward
// neural-network node which
// can be used by the ADALINEs
// and Backprop networks
//##ModelId=3A1160DB03DE
class Feed_Forward_Node : public Base_Node  
{
protected:
	//##ModelId=3A1160DC000B
	virtual double Transfer_Function(double value); // Transfer_Function(Activatve Funztion)을 위한 가상함수
public:
	//##ModelId=3A1160DC0028
	Feed_Forward_Node(int v_size = 1, int e_size = 1);	// Constructor
	//##ModelId=3A1160DC0034
	virtual void Run(int mode =0);
	//##ModelId=3A1160DC0046
	virtual char *Get_Name(void);

};

//##ModelId=3A1160DC000B
double Feed_Forward_Node::Transfer_Function(double value)
{
	return value;
};

//##ModelId=3A1160DC0028
Feed_Forward_Node::Feed_Forward_Node(int v_size, int e_size) : Base_Node(v_size, e_size)
{

};

//##ModelId=3A1160DC0034
void Feed_Forward_Node::Run(int mode)
{
	in_links.Reset_To_Head();	// Reset of links
	double total = 0.0;			// Initialize of Input weight
	int cnt=in_links.Count();	// Count value of Links

	for(int i=0 ; i < cnt; i++)	// For each node's input link
	{
		total += in_links.Curr()->Weighted_In_Value(); // Get of Input weight value and add total weight
		in_links.Next();	// Next Link
	}
	value[mode] = Transfer_Function(total);
};

//##ModelId=3A1160DC0046
char *Feed_Forward_Node::Get_Name(void)
{
	static char name[]="Feed_Forward_Node";
	return name;
};

//##ModelId=3A1160DC0262
class Base_Network : public Base_Node	// Base Network Node
{
protected:
	//##ModelId=3A1160DC0281
	int num_nodes;			// Number of nodes in Network
	//##ModelId=3A1160DC0295
	int num_links;			// Number of links in network
	//##ModelId=3A1160DC02B4
	Base_Node **node;		// Array of base nodes
	//##ModelId=3A1160DC02E5
	Base_Link **link;		// Array of base links

	//##ModelId=3A1160DC0303
	virtual void Create_Network(void);
	//##ModelId=3A1160DC0317
	virtual void Load_Inputs(void);
	//##ModelId=3A1160DC032B
	virtual void Save_Nodes_Links( ofstream &outfile);
	//##ModelId=3A1160DC0349
	virtual void Load_Nodes_Links( ifstream &infile);
public:
	//##ModelId=3A1160DC035D
	Base_Network(void);		// Constructor
	//##ModelId=3A1160DC0367
	~Base_Network(void);	// Destructor
	//##ModelId=3A1160DC037B
	virtual void Epoch(int code=0);
	//##ModelId=3A1160DC038F
	virtual void Print( ofstream &outfile);
	//##ModelId=3A1160DC0399
	virtual char *Get_Name(void);

};

//##ModelId=3A1160DC0303
void Base_Network::Create_Network(void)
{  
	
};

//##ModelId=3A1160DC0317
void Base_Network::Load_Inputs(void)
{   
};

//##ModelId=3A1160DC032B
void Base_Network::Save_Nodes_Links( ofstream &outfile)
{   
	outfile << num_nodes << endl;
	outfile << num_links << endl;
	for(int i=0; i < num_nodes ; i++)		// Store all nodes
		node[i]->Save(outfile);
	for(int i=0 ; i < num_links; i++)			// Store all links
		link[i]->Save(outfile);
};

//##ModelId=3A1160DC0349
void Base_Network::Load_Nodes_Links( ifstream &infile)
{  
	infile >> num_nodes;
	infile >> num_links;

	Create_Network();
	for(int i = 0; i < num_nodes ; i++)		// Load all nodes
		node[i]->Load(infile);	
	for(int i=0; i < num_links; i++)			// Load all links
		link[i]->Load(infile);
}

//##ModelId=3A1160DC035D
Base_Network::Base_Network(void) : Base_Node( 0, 0)	// Constructor
{
	num_nodes = 0;
	num_links = 0;
	node = NULL;
	link = NULL;
};

//##ModelId=3A1160DC0367
Base_Network::~Base_Network(void)				// Destructor
{
	if(node !=NULL )
	{
		for(int i=0; i < num_nodes; i++)		// Free all nodes
			delete node[i];
		for(int i = 0; i < num_links; i++)			// Free all links
			delete link[i];
		delete []node;
		delete []link;
	}
};

//##ModelId=3A1160DC038F
void Base_Network::Print( ofstream &outfile)
{   
	for (int i = 0; i < num_nodes; i++)		// Print each node in network
		node[i]->Print(outfile);
};

//##ModelId=3A1160DC0399
char *Base_Network::Get_Name(void)
{   
	static char name[]="BASE_NETWORK";
	return name;
};

//##ModelId=3A1160DC037B
void Base_Network::Epoch(int code)
{   
	for(int i=0; i < num_nodes; i++)	// Run Epoch for each node in network
		node[i]->Epoch(code);
	for(int i =0; i < num_links; i++)		// Run Epoch for each link in network
		link[i]->Epoch(code);
}

// --------------------------------------------
// Linked-List Constructor

//##ModelId=3A1160D90290
LList::LList(void)
{
	curr=head=tail=NULL;
	count=0;
}

//##ModelId=3A1160D9029B
LList::~LList(void)
{
	Clear();
}

//##ModelId=3A1160D90308
int LList::Count(void)
{
	return count;
}
// ---------------------------------------
// Clear out the contents of a list
//##ModelId=3A1160D902F5
void LList::Clear(void)
{
	NODE *i=head, *temp;

	while(i != NULL)
	{
		temp = i;
		i = i->next;
		delete temp;
	}
	curr=head=tail=NULL;
	count =0;
}
// ----------------------------------------
// Add an element to the tail of a list
//##ModelId=3A1160D902AE
int LList::Add_To_Tail(Base_Link *element)
{
	curr=NULL;
	return Add_Node(element);
}
// -------------------------------------------------------------------
// This function add a node before the node curr points to. If curr is
// NULL then the node is added to the tail of the list
//##ModelId=3A1160D902B8
int LList::Add_Node(Base_Link *element)
{
	NODE *temp=new NODE;

	if(temp == NULL)
	{
		cout << "Unable to allocate Node..." << endl;
	}

	temp->element = element;

	if(temp == NULL)
		return 0;

	if(curr==NULL)
	{
		temp->prev=tail;
		temp->next=NULL;

		if(tail == NULL)
		{
			head=temp;
			tail=temp;
		}
		else
		{
			tail->next = temp;
			tail=temp;
		}
	}
	else if(curr == head)
	{
		temp->prev= NULL;
		temp->next= head;
		if(head == NULL)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			head->prev = temp;
			head = temp;
		}
	}
	else
	{
		temp->prev=curr->prev;
		temp->next=curr;
		curr->prev->next = temp;
		curr->prev = temp;
	}
	count++;
	return 1;
}
// --------------------------------------------------------------------
// Function to verify existence of element in list and returns position
//##ModelId=3A1160D902EA
int LList::Find(Base_Link *element)
{
	NODE *temp=head;
	int cnt=1;
	curr = NULL;

	while(temp != NULL)
	{
		if(temp->element == element)
		{
			curr=temp;
			return cnt;
		}
		cnt++;
		temp=temp->next;
	}
	return 0;
}
// ------------------------------------------------------------------------
// Deletes an element anywhere in a list(first occurence)
//##ModelId=3A1160D902E0
int LList::Del(Base_Link *element)
{
	if(!Find(element))
		return 0;
	return Del_Node();
}
// -------------------------------------------------------------------------
// This function deletes the current node in the list(curr)
//##ModelId=3A1160D902CC
int LList::Del_Node(void)
{
	if(curr == NULL)
		return 0;
	delete curr->element;

	if(curr == head)
	{
		if(head==tail)
			tail=NULL;
		else head->next->prev=NULL;
			head = curr->next;
	}
	else if(curr==tail)
	{
		tail->prev->next=NULL;
		tail = curr->prev;
	}
	else
	{
		curr->next->prev = curr->prev;
		curr->prev->next = curr->next;
	}
	delete curr;
	curr = NULL;
	count--;
	return 1;
}
// ------------------------------------------------------------------------
// Reset current node position (curr) to head of list
//##ModelId=3A1160D90312
void LList::Reset_To_Head(void) 
{
	curr = head;
}
// ------------------------------------------------------------------------
// Reset current node position (curr) to tail of list
//##ModelId=3A1160D9031D
void LList::Reset_To_Tail(void)
{
	curr = tail;
}
// ------------------------------------------------------------------------
// Return the Current element pointed to in the Container
//##ModelId=3A1160D90330
Base_Link *LList::Curr(void)
{
	if(curr == NULL)
		return NULL;
	else 
		return curr->element;
}
// ------------------------------------------------------------------------
// Advances current node
//##ModelId=3A1160D9033B
void LList::Next(void)
{
	if(curr->next == NULL)
		curr=head;
	else 
		curr = curr->next;
}
// ------------------------------------------------------------------------
// Mode the current node backwards
//##ModelId=3A1160D9034E
void LList::Prev(void)
{
	if(curr->prev == NULL)
		curr = tail;
	else
		curr = curr->prev;
}

#endif BASE
