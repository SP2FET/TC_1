#include <iostream>

using namespace std;


struct node_t
{
	bool visited;
	int color;
	struct edge_t *edges;
	struct node_t *next_node;
	struct node_t *return_node;
	int number;
	node_t();
};


struct edge_t
{
	  struct node_t *connected_node;
	  struct edge_t *next_edge;
};

node_t::node_t()
{
	number = 1;
	next_node = 0;
	return_node = 0;
	visited = 0;
	color=0;
	edge_t *edge = new edge_t;
	edge->connected_node = 0;
	edge->next_edge = 0;
	edges = edge;
}
struct graph_t
{
	struct node_t *first_node;
	struct node_t *actual_node;
	int nodes_amount;

	graph_t();
	void add_edge(node_t *&parent, node_t *&child);
	void add_node(node_t *&parent);
	void clear_visited_flags();
	void paint_graph(node_t *&parent);
	void give_color(node_t *&parent);

	node_t* get_node(int number);
};

graph_t::graph_t()
{
	node_t *init_node = new node_t;
	nodes_amount = 1;
	first_node = init_node;
	actual_node = first_node;
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

	new_node->number = nodes_amount + 1;

	if(parent->next_node == 0) parent->next_node = new_node;
	else
	{
		temp_node = parent;
		while(temp_node->next_node) //szukanie ostatniej krawedzi
			  temp_node = temp_node->next_node;
		temp_node->next_node = new_node;
	}

	add_edge(parent,new_node);
	add_edge(new_node,parent);
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

void graph_t::clear_visited_flags()
{
    node_t *temp_node=first_node;

    temp_node->visited=false; // dla pierwszego wezla

     while(temp_node->next_node)
    {
        temp_node=temp_node->next_node;
        temp_node->visited=false;
    }
}


void graph_t::give_color(node_t *&parent)
{
   node_t *temp_node=parent;
   edge_t *start_edge=temp_node->edges;
   int proposed_color=0;
   bool found_color=false;

   while(!found_color)
   {
    cout<<"TEST3 "<< proposed_color<< endl;

      while(!found_color && temp_node->edges->next_edge) //jesli nie znaleziono jeszcze koloru albo nie skonczyla sie liczba krawedzi
      {
        found_color=true;

          if(proposed_color==temp_node->edges->connected_node->color)
          {
              found_color=false;
              cout<<"TEST2 - "<<proposed_color<<endl;
              break;
          }
          temp_node->edges=temp_node->edges->next_edge; //porownuje z nastepnym wezlem
      }

     if(!found_color) proposed_color++;
    temp_node->edges=start_edge;
   }

   temp_node->color=proposed_color;
   cout<<"Node "<<temp_node->number<<" has given "<<temp_node->color<<" color"<<endl;
}

void graph_t::paint_graph(node_t *&parent) //jako pierwszy parametr podajemy wezel, od ktorego zaczynamy
{

    bool entering_new_node=true;
    int checked_nodes_amount=0;

    node_t *temp_node=parent;
    node_t *bufor_node;

    clear_visited_flags();

        while(checked_nodes_amount<nodes_amount)
        {
            entering_new_node=true;

             if(!temp_node->visited)
            {
                checked_nodes_amount++; //zabezpieczebie zeby sie nie dodalo kilka razy
                temp_node->visited=true;
            }

             if(checked_nodes_amount==nodes_amount) break;

            //give_color(temp_node);

            while(temp_node->edges->connected_node->visited) // dopoki nastepny wezel z listy polaczen wezel zostal odwiedzony
            {
                cout<<"TESTING EDGE FROM "<<temp_node->number<<" TO "<<temp_node->edges->connected_node->number<<endl;
                if(!temp_node->edges->next_edge) //jesli dotarlismy do ostatniego polaczenia i bylo odwiedzone - wszystkie drogi juz odwiedzilismy
                {                                //UWAGA - nie dziala jesli jestesmy w poczatkowym wezle bo return_node nie jest okreslony
                    cout<<"TESTX"<<endl;
                    temp_node=temp_node->return_node; // powracamy do wezla, z ktorego przyszlismy
                    entering_new_node=false;
                    break;
                }

                temp_node->edges=temp_node->edges->next_edge; //sprawdzamy nastepne polaczenie
            }

            cout<<"TEST1"<<endl;

           if(entering_new_node) // jesli odnazliono jakis nieodwiedzony wezel
           {
               cout<<"GOING FROM "<<temp_node->number<<" TO "<<temp_node->edges->connected_node->number<<endl;
               bufor_node=temp_node;
               temp_node=temp_node->edges->connected_node;
               temp_node->return_node=bufor_node;
           }

        }

}

int main()
{
	graph_t *graph = new graph_t;

	node_t *num_node;
	num_node = graph->get_node(0);
	graph->add_node(graph->first_node);
	graph->add_node(graph->first_node->next_node);
	graph->add_node(graph->first_node->next_node->next_node);
	graph->add_node(graph->first_node->next_node->next_node);

	//graph->add_edge(graph->first_node, graph->first_node->next_node->next_node);


	for(int i = 1; i <= graph->nodes_amount; i++)
	{
		num_node = graph->get_node(i);
		if(num_node != 0) cout<<"node: "<<i<<" by number: "<<num_node->number<<endl;
	}

	graph->paint_graph(graph->first_node);

	delete graph;
	cout<<"OK"<<endl;
    return 0;
}





