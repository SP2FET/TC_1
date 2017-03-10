#include <iostream>

using namespace std;

struct node_t
{
	struct edge_t{
	  edge_t *next_edge;
	  node_t *node;
	}*edge; //wskaznik na element listy krawedzi
	
	int number; //numer wezla
		
	node_t() {edge->next_edge = NULL;}	
	int get_number() { return number;}
	
	void create_edge(node_t *&parent, node_t *&child);
	
};

void node_t::create_edge(node_t *&parent, node_t *&child)
{
	edge_t *new_edge = new edge_t;

	new_edge->node = child;
	if(parent->edge->next_edge == 0) //pierwszy element listy
	{
		parent->edge->next_edge = new_edge;
	}
	else
	{

		while(parent->edge->next_edge) //szukanie ostatniej krawedzi
			parent->edge = parent->edge->next_edge;
			
		parent->edge->next_edge = new_edge;
	}
	
	
}

struct graph_t
{
	node_t *actual_node;
	node_t *first_node;
	int nodes_amount;
	
	
	int create_node(node_t *&parent_node);
	graph_t();
	int get_nodes_amount() { return nodes_amount; }

};

graph_t::graph_t()
{
	nodes_amount = 1;
	node_t *new_init_node = new node_t;
	new_init_node->number = 1;
	new_init_node->edge->next_edge = 0;
	new_init_node->edge->node = 0;
	first_node = new_init_node;
	actual_node = first_node;
	
}
	


int graph_t::create_node(node_t *&parent_node)
{
	cout<<"create init"<<endl;
	node_t *node_to_add = new node_t;
//	
//	node_to_add->number = nodes_amount + 1;
//	
//	nodes_amount += 1;
//	//node_to_add->create_edge(parent_node, node_to_add);
//	cout<<"Node "<<node_to_add->number<<" created"<<endl;
//	return node_to_add->number;
	
}
//
//bool search_node(node *next_node, node *&found_node, short node_name) //jako pierwszy parametr podajemy wezel, od ktorego zaczynamy
//{
//    bool wanted_node_exists=false;
//    node *bufor;
//
//        while(	1/*tu nie wiem co, trzeba jakos sprawdzic czy nie sprawdzilo sie juz wszystkich wezlow*/)
//        {
//            while(next_node->actual_connections->child.visited) // dopoki nastepny wezel z listy polaczen wezel zostal odwiedzony
//            {
//                if(next_node->actual_connections->next==NULL) //jesli dotarlismy do ostatniego polaczenia i bylo odwiedzone - wszystkie drogi juz odwiedzilismy
//                {
//                    next_node=previous_node; // powracamy do wezla, z ktorego przyszlismy
//                    break;
//                }
//
//                next_node->actual_connection=next_node->actual_connection->next; //sprawdzamy nastepne polaczenie
//            }
//
//            bufor=next_node;
//            next_node=next_node->actual_connection->child; // jesli odnazliono jakis nieodwiedzony wezel
//            next_node->previous_node=bufor;
//
//            if(next_node.name!=node_name)
//            {
//                found_node=next_node;
//                wanted_node_exists=true;
//            }
//
//            next_node.visited=true;
//        }
//
//        return wanted_node_exists;
//}
//
//
//bool add_connection(short child_name, short parent_name)
//{
//   node *parent;
//   node *child;
//
//   if(search_node(parent,parent_name))
//    {
//
//    }
//     else cout<<"Nie znaleiono wezla-rodzica!"<<endl;
//
//}


int main()
{

 //node *first_node=NULL;

//	node_t *node = new node_t;
	int num;
	graph_t graph;
	cout<<"init"<<endl;
	num = graph.create_node(graph.actual_node);
	
	cout<<"node number = "<<graph.actual_node->number<<" New number: "<<num<<endl;
	//delete graph;
system("dir");
    return 0;
}
