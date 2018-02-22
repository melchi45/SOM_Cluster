//****************************************************************************
//  File Name	: GenBP.h
//	Purpose		: Generic Steepnessagation Neural Network Class
//  Creator		: Young ho Kim<melchi@nownuri.net>
//				  MFC Forum <http://stmail.chosun.ac.kr/~melchi/>
//****************************************************************************

#include <stdio.h>
#include <fstream.h>
#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>
#include "Steepness.h"
#include "Common.h"

//##ModelId=3A1160D6006F
template<class INPUT_NODE, class HIDDEN_NODE, class OUTPUT_NODE, class LINK>
class Generic_Steepness : public Steepness_Network
{
	public:
	//##ModelId=3A1160D60097
		Generic_Steepness(char *filename);
	//##ModelId=3A1160D600A1
		Generic_Steepness(double lr, double mt, double b, int layers, ...);
	//##ModelId=3A1160D600BF
		Generic_Steepness(void) : Steepness_Network(){};
	//##ModelId=3A1160D600C9
		Generic_Steepness(double lr, double mt, double b, int layers, int nodes[]);

	//##ModelId=3A1160D600DE
		virtual void Create_Network(void);

	//##ModelId=3A1160D600F2
		char *Get_Name(void)
		{
			static char name[] = "Generic_Steepness_Network";
			return name;
		};
};		

template<class INPUT_NODE, class HIDDEN_NODE, class OUTPUT_NODE, class LINK>
	Generic_Steepness<INPUT_NODE, HIDDEN_NODE, OUTPUT_NODE, LINK>::
	Generic_Steepness(char filename[]) : 
		Steepness_Network()
{
	ifstream infile(filename);
	Load(infile);
	infile.close();
};

//##ModelId=3A1160D600A1
template<class INPUT_NODE, class HIDDEN_NODE, class OUTPUT_NODE, class LINK>
	Generic_Steepness<INPUT_NODE, HIDDEN_NODE, OUTPUT_NODE, LINK>::
	Generic_Steepness(double lr, double mt, double b, int layers, ...) : 
		Steepness_Network()
{
	num_nodes = 0;
	num_links = 0;

	num_layers = layers;
	va_list vl;
	va_start(vl, layers);
	node_cnt = new int[layers];

	for(int i=0; i<layers; i++)
	{
		node_cnt[i] = va_arg(vl, int);
		num_nodes += node_cnt[i];

		if( i > 0)
			num_links += node_cnt[i-1] * node_cnt[i]; // links between layers
	}

	va_end(vl);

	learning_rate = lr;
	momentum_term = mt;
	beta = b;

	Create_Network();
};

template<class INPUT_NODE, class HIDDEN_NODE, class OUTPUT_NODE, class LINK>
	Generic_Steepness<INPUT_NODE, HIDDEN_NODE, OUTPUT_NODE, LINK>::
	Generic_Steepness(double lr, double mt, int layers, double b, int nodes[]) : 
		Steepness_Network()
{
	num_nodes = 0; 
	num_links = 0;

	num_layers = layers;
	node_cnt = new int[layers];

	for(int i = 0; i<layers; i++)
	{
		node_cnt[i] = nodes[i];
		num_nodes += node_cnt[i];

		if(i > 0)
			num_links += node_cnt[i-1] * node_cnt[i]; // link between layers
	}

	learning_rate = lr;
	momentum_term = mt;
	beta = b;

	Create_Network();
};

//##ModelId=3A1160D600DE
template<class INPUT_NODE, class HIDDEN_NODE, class OUTPUT_NODE, class LINK>
void Generic_Steepness<INPUT_NODE, HIDDEN_NODE, OUTPUT_NODE, LINK>::
	Create_Network(void)
{
	node = new Base_Node*[num_nodes];
	link = new Base_Link*[num_links];

	int curr = 0;
	for(int i = 0; i < node_cnt[0]; i++)
		node[curr++] = new INPUT_NODE;

	first_hidden_node = curr;
	for(i=1; i < num_layers-1; i++)
		for(int j = 0 ; j < node_cnt[i]; j++)
			node[curr++] = new HIDDEN_NODE(learning_rate, momentum_term, beta);

	first_output_node = curr;

	for(i = 0; i < node_cnt[num_layers-1] ; i++)
		node[curr++] = new OUTPUT_NODE(learning_rate, momentum_term, beta);

	for(i = 0; i < num_links; i++)
		link[i] = new LINK;

	curr = 0;

	int layer1 = 0, layer2 = first_hidden_node;

	for(i= 0; i < num_layers -1 ; i++)
	{
		for(int j=0; j<node_cnt[i+1]; j++)
			for(int k =0; k < node_cnt[i]; k++)
				Connect(node[layer1+k], node[layer2+j], link[curr++]);

		layer1 = layer2;
		layer2 += node_cnt[i+1];
	}
};
