#include <iostream>

using namespace std;

//#define ENABLE_DEFAULT_EDGES

struct node_t 
{				  
	bool visited;
	struct edge_t *edges;
	struct node_t *next_node;
	int number;
	int edges_number;
	node_t();
};

node_t::node_t()
{
	number = 1;
	edges_number = 0;
	next_node = 0;
	visited = 0;
	edge_t *edge = new edge_t;
	edges = edge;
}

struct edge_t 
{
	  struct node_t *connected_node;
	  struct edge_t *next_edge;
	  edge_t();
};

edge_t::edge_t()
{
	connected_node = 0;
	next_edge = 0;
}

struct graph_t
{
	struct node_t *first_node;
	struct node_t *actual_node;
	int nodes_amount;
	
	graph_t();
	void add_edge(node_t *parent, node_t *child);
	void add_node(node_t *&parent);
	bool delete_node(int node_number);
	bool delete_edge(node_t *&parent, node_t *&child);
	node_t* get_node(int number);
};

graph_t::graph_t()
{
	node_t *init_node = new node_t;
	nodes_amount = 1;
	first_node = init_node;
	actual_node = first_node;
}			

void graph_t::add_edge(node_t *parent, node_t *child)
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
		parent = temp_node;
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
		while(temp_node->edges->next_edge) //szukanie ostatniej krawedzi
			  temp_node->edges = temp_node->edges->next_edge;
		temp_node->edges->next_edge = new_edge_child;
		child = temp_node;
	}
	child->edges_number += 1;
	parent->edges_number += 1;
	
}

void graph_t::add_node(node_t *&parent)
{
	node_t *new_node = new node_t;
	node_t *temp_node;
	
	new_node->number = nodes_amount + 1;
	
	if(parent->next_node == 0) parent->next_node = new_node;
	else 
	{
		temp_node = parent;
		while(temp_node->next_node) //szukanie ostatniej krawedzi
			  temp_node = temp_node->next_node;
		temp_node->next_node = new_node;
	}
	
	#ifdef ENABLE_DEFAULT_EDGES
	add_edge(parent,new_node);
	add_edge(new_node,parent);
	#endif
	
	nodes_amount +=1;
}

node_t* graph_t::get_node(int node_number)
{
	node_t *temp_node;
	if( first_node->number == node_number ) // gdy szukany wezel jest pierwszym
	{		
		return first_node;
	}
	else 
	{		
		temp_node = first_node;
		
		while(temp_node->number != node_number) 
		{			
			if(temp_node->next_node == 0) return 0;
			temp_node = temp_node->next_node;
		}		
		return temp_node;
	}
}

bool graph_t::delete_edge(node_t *&parent, node_t *&child)
{
	edge_t *temp_edge;
	temp_edge = parent->edges;
	int amount = nodes_amount;
	// parent -> child
	if(temp_edge->connected_node == child) //pierwsza krawedz  na liscie
	{
		//temp_edge = parent->edges;
		parent->edges = temp_edge->next_edge; 
		delete temp_edge;
		//druga krawedz
	}
	else
	{

		while(temp_edge->next_edge->connected_node != child)
			{
				temp_edge = temp_edge->next_edge;
				if(--amount == 0) return 1;
			}
		
		temp_edge = temp_edge->next_edge->next_edge;
		parent->edges = temp_edge;
		delete temp_edge;
	}
	
	//child -> parent
	amount = nodes_amount;
	if(child->edges->connected_node == parent) //pierwsza krawedz
	{
		temp_edge = child->edges;
		child->edges = temp_edge->next_edge; 
		delete temp_edge;
		//druga krawedz
	}
	else
	{

		while(temp_edge->next_edge->connected_node != parent)
			{
				temp_edge = temp_edge->next_edge;
				if(--amount == 0) return 1;
			}
		
		temp_edge = temp_edge->next_edge->next_edge;
		child->edges = temp_edge;
		delete temp_edge;
	}
	return 0;
}

bool graph_t::delete_node(int node_number)
{
	node_t *parent_node, *child_node, *act_node, *temp_node;
	edge_t *act_edge, *edge_to_del;
	
	if(node_number < 2) return 1;
	
	parent_node = get_node(node_number-1);
	act_node = parent_node->next_node;
	child_node = act_node->next_node;
	
	parent_node->next_node = child_node;
	
	act_edge = act_node->edges;
	cout<<"first edge: "<<act_node->edges->connected_node->number<<endl;
	while (act_edge != NULL) //usuwa listê krawêdzi z wêz³a do usuniêcia
	{
		
		edge_to_del = act_edge;
		act_edge = act_edge->next_edge;
		cout<<"deleting edge: "<<edge_to_del->connected_node->number<<endl;
		delete edge_to_del;
	}
	
	
	
	temp_node = first_node;
		while(temp_node->next_node) //leci po wszystkich wezlach
		{
			
			temp_node = temp_node->next_node;
			cout<<"deleting edge from: "<<temp_node->number<<endl;
			if(temp_node == act_node) continue;
			if (temp_node->number > act_node->number) temp_node->number -= 1;
			act_edge = act_node->edges;
			
			while (act_edge != NULL) //usuwa krawedz laczaca kolejny wezel z usuwanym
			{
				
				edge_to_del = act_edge;
				cout<<"edge scan: "<<edge_to_del->connected_node->number<<endl;
				act_edge = act_edge->next_edge;
				
				if(edge_to_del->connected_node == act_node) delete edge_to_del;
			}
			
				
		}
			  
			  //po wszystkich wezlach:
	delete act_node;
	nodes_amount -= 1;

}

int main()
{
	graph_t *graph = new graph_t;
	
	node_t *num_node;
	edge_t *num_edge;
	graph->add_node(graph->first_node);
	graph->add_node(graph->first_node->next_node);
	graph->add_node(graph->first_node->next_node->next_node);
	graph->add_node(graph->first_node->next_node->next_node->next_node);
	//graph->add_node(graph->first_node->next_node->next_node->next_node->next_node);
	
	graph->add_edge(graph->get_node(1), graph->get_node(2));
	graph->add_edge(graph->get_node(1), graph->get_node(4));
	graph->add_edge(graph->get_node(2), graph->get_node(3));
	graph->add_edge(graph->get_node(3), graph->get_node(4));
	graph->add_edge(graph->get_node(4), graph->get_node(5));
	graph->add_edge(graph->get_node(3), graph->get_node(5));
	
	for(int i = 1; i <= graph->nodes_amount; i++)
	{
		num_node = graph->get_node(i);
		num_edge = num_node->edges;
		cout<<"node: "<<num_node->number<<" is connected with: ";
		
		
		while (num_edge != NULL) 
		{
		
			if (num_edge->connected_node != 0)/* cout<<"none "<<endl;*/
			/*else*/ cout<<num_edge->connected_node->number<<" ";
			
			num_edge = num_edge->next_edge;
			
			
		}
		cout<<endl;
	}
	graph->delete_node(4);
	cout<<endl;
		for(int i = 1; i <= graph->nodes_amount; i++)
	{
		num_node = graph->get_node(i);
		num_edge = num_node->edges;
		cout<<"node: "<<num_node->number<<" is connected with: ";
		
		while (num_edge != NULL) 
		{
		
			if (num_edge->connected_node != 0)/* cout<<"none "<<endl;*/
			/*else*/ cout<<num_edge->connected_node->number<<" ";
			
			num_edge = num_edge->next_edge;
			
			
		}
		cout<<endl;
	}
	delete graph;
	cout<<"OK"<<endl;
    return 0;
}
