#include <iostream>

using namespace std;


struct node_t 
{				  
	int visited;
	struct edge_t *edges;
	struct node_t *next_node;
	
	node_t();
};


struct edge_t 
{
	  struct node_t *connected_node;
	  struct edge_t *next_edge;
};

node_t::node_t()
{
	edge_t *edge = new edge_t;
	edge->connected_node = 0;
	edge->next_edge = 0;
	edges = edge;
}
struct graph_t
{
	struct node_t *first_node;
	int nodes_amount;
	
	graph_t();
	void add_edge(node_t *&parent, node_t *&child);
	void add_node(node_t *&parent);
};

graph_t::graph_t()
{
	node_t *init_node = new node_t;
	init_node->visited = 0;

	init_node->next_node = 0;	
	
	init_node->edges->connected_node = 0;
	init_node->edges->next_edge = 0;
	
	nodes_amount = 1;
	first_node = init_node;
}			

void graph_t::add_edge(node_t *&parent, node_t *&child)
{
	edge_t *new_edge_parent = new edge_t;
	new_edge_parent->connected_node = child;
	new_edge_parent->next_edge = 0;
	node_t *temp_node;
	
	if(parent->edges->next_edge == 0)
	{
		parent->edges->next_edge = new_edge_parent;
	}else
	{
		temp_node = parent;
		while(temp_node->edges->next_edge) //szukanie ostatniej krawedzi
			  temp_node->edges = temp_node->edges->next_edge;
		temp_node->edges->next_edge = new_edge_parent;
		
	}
	
	edge_t *new_edge_child = new edge_t;
	new_edge_child->connected_node = parent;
	new_edge_child->next_edge = 0;
	
	if(child->edges->next_edge == 0)
	{
		child->edges->next_edge = new_edge_child;
		
	}else
	{
		
		temp_node = child;
		while(child->edges->next_edge) //szukanie ostatniej krawedzi
			  child->edges = child->edges->next_edge;
		child->edges->next_edge = new_edge_child;
	}
	
}

void graph_t::add_node(node_t *&parent)
{
	node_t *new_node = new node_t;
	node_t *temp_node;
	new_node->visited = 0;
	if(parent->next_node == 0) parent->next_node = new_node;
	else 
	{
		temp_node = parent;
		while(temp_node->next_node) //szukanie ostatniej krawedzi
			  temp_node = temp_node->next_node;
		temp_node->next_node = new_node;
	}
	new_node->next_node = 0;
	add_edge(parent,new_node);
	add_edge(new_node,parent);
	nodes_amount +=1;
}
int main()
{
	graph_t *graph = new graph_t;
	
	graph->add_node(graph->first_node);
	graph->add_node(graph->first_node->next_node);
	graph->add_node(graph->first_node->next_node->next_node);
	graph->add_edge(graph->first_node, graph->first_node->next_node->next_node);
	for(int i = 1; i <= graph->nodes_amount; i++)
	{
		cout<<"node: "<<i<<" "<<endl;
	}
	delete graph;
	cout<<"OK"<<endl;
    return 0;
}
