#include <iostream>

using namespace std;


#define ENABLE_NUMBER_CHANGE

struct node_t
{
	int number;
	int color;
	bool visited;
	node_t *next_node;
    node_t *return_node;
	node_t();
};

node_t::node_t()
{
	next_node = NULL;
	number = 1;
    visited=false;
	color=0;
}

struct edge_t
{
	node_t *left_node;
	node_t *right_node;
	edge_t *next_edge;
	edge_t();
};

edge_t::edge_t()
{
	left_node = NULL;
	right_node = NULL;
	next_edge = NULL;
}

struct graph_t
{
	edge_t *edges_list;
	node_t *nodes_list;

	graph_t();
	void add_edge(node_t* left, node_t* right);
	node_t* add_node();
	edge_t* get_last_edge();
	node_t* get_last_node();
	node_t* get_node(int node_number);
	void	add_nodes(int amount);
	void	delete_node(int node_number);
	void 	delete_edge(node_t* left, node_t* right);
	void 	draw();

	void    clear_visited_flags();
    int     count_nodes();
	void    paint_graph(node_t *start_node);
	//void    give_color(node_t *start_node);
	bool    search_edges(node_t *parent_node, node_t *&child_node, edge_t *&start_edge);

}

graph_t::graph_t()
{
	edges_list = NULL;
	nodes_list = NULL;
}

edge_t* graph_t::get_last_edge()
{
	edge_t *last_edge;
	last_edge = edges_list;
	if(last_edge == NULL) return last_edge;
	while(last_edge->next_edge)
		last_edge = last_edge->next_edge;
	return last_edge;
}

node_t* graph_t::get_last_node()
{

	node_t *last_node;
	last_node = nodes_list;
	if(last_node == NULL) return last_node;
	while(last_node->next_node)
		last_node = last_node->next_node;

	return last_node;
}

node_t*  graph_t::get_node(int node_number)
{
		//zab pzed numerem z poza zakresu
	node_t *temp_node = nodes_list;

	if(temp_node == NULL || (temp_node->number == node_number)) return temp_node;
	while(temp_node)
	{
		if(temp_node->number == node_number) return temp_node;
		if(temp_node->next_node == NULL) break;
		temp_node = temp_node->next_node;
	}


}

void graph_t::add_edge(node_t* left, node_t* right)
{

	if (left == right) return;

	edge_t *new_edge = new edge_t();

	new_edge->left_node = left;
	new_edge->right_node = right;




	if(edges_list == NULL)
	{

		edges_list = new_edge;
	}
	else
	{
		edge_t *last_edge = get_last_edge();
		last_edge->next_edge = new_edge;
	}


	//TODO: if + while do sprawdzania klon�w i czy left nie = right
}

void graph_t::delete_edge(node_t* left, node_t* right)
{
	if(left == NULL || right == NULL || left == right) return;

	edge_t *edge_to_delete, *temp_edge;
	bool cond_1, cond_2;
	temp_edge = edges_list;
	if(temp_edge == NULL) return;
	if(temp_edge->next_edge == NULL) //tylko jedna krawedz
	{
		cond_1 = (temp_edge->left_node == left) && (temp_edge->right_node == right);
		cond_2 = (temp_edge->left_node == right) && (temp_edge->right_node == left);
		if(cond_1 || cond_2)
		{
			delete temp_edge;
			edges_list = NULL;
		}
		else
			return;
	}
	else if ((temp_edge->left_node == left && temp_edge->right_node == right) || (temp_edge->left_node == right && temp_edge->right_node == left))
		{
			edge_to_delete = temp_edge;
			edges_list->next_edge = temp_edge->next_edge;
			delete edge_to_delete;
			return;
		}
		else //wiecej niz jedna
		{

		do
		{
			cond_1 = (temp_edge->next_edge->left_node == left) && (temp_edge->next_edge->right_node == right);
			cond_2 = (temp_edge->next_edge->left_node == right) && (temp_edge->next_edge->right_node == left);
			if(cond_1 || cond_2)//nastepny element jest do usuniecia
			{
				if(temp_edge->next_edge->next_edge == NULL) //element do usuniecia jest ostatni
				{
					edge_to_delete = temp_edge->next_edge;
					temp_edge->next_edge = NULL;
					delete edge_to_delete;
					return;

				}else //element do usuniecia jest pomiedzy dwoma innymi
				{
					edge_to_delete = temp_edge->next_edge;
					temp_edge->next_edge = temp_edge->next_edge->next_edge;
					delete edge_to_delete;
					return;
				}
			}else //nast�pny element nie jest do usuniecia
			{
			if(temp_edge->next_edge->next_edge == NULL) break;
			temp_edge = temp_edge->next_edge;
			}
		//	cout<<"test"<<endl;


		}while(temp_edge);
	return;
	}

}


node_t* graph_t::add_node()
{
	node_t *new_node =  new node_t();

	if(nodes_list == NULL)
	{

		nodes_list = new_node;
		new_node->number = 1;
	}
	else
	{
		node_t *last_node = get_last_node();
		new_node->number = last_node->number + 1;
		last_node->next_node = new_node;
	}

	return new_node;

}

void graph_t::add_nodes(int amount)
{
	for(int i = 0; i < amount; i++)
		add_node();
}

void graph_t::draw() {

	node_t *temp_node = nodes_list;

	if(temp_node == NULL || edges_list == NULL) return;

	do
	{
		cout<<"node "<<temp_node->number<<" is connected with: ";
		edge_t *temp_edge = edges_list;

		do
		{

			if(temp_edge->left_node == temp_node)
			{
				cout<<temp_edge->right_node->number<<" ";
			}
			else if(temp_edge->right_node == temp_node)
			{
				cout<<temp_edge->left_node->number<<" ";
			}

			//if(temp_edge == NULL) break;
			temp_edge = temp_edge->next_edge;

		}while(temp_edge);

		//if(temp_node == NULL) break;
		temp_node = temp_node->next_node;

		cout<<endl;
	}while(temp_node);
}


void graph_t::delete_node(int node_number)
{



	node_t *node_to_delete, *prev_node, *nxt_node;
	//zab pzed numerem z poza zakresu
	prev_node = get_node(node_number-1);

	if(prev_node == NULL || (prev_node->next_node == NULL)) return;
	node_to_delete = prev_node->next_node;

	node_t *temp_node = nodes_list;

		do
		{

			//cout<<"node to delete: "<<node_to_delete<<" temp_node: "<<temp_node<<endl;

				delete_edge(node_to_delete, temp_node);
			#ifdef ENABLE_NUMBER_CHANGE
			if(temp_node->number > node_number) temp_node->number -= 1;
			#endif
			//if(temp_node == NULL) break;
			temp_node = temp_node->next_node;

		}while(temp_node);



	if(node_to_delete->next_node == NULL) //ostatni element
	{
		prev_node->next_node = NULL;
	}
	else
	{
		nxt_node = node_to_delete->next_node;
		prev_node->next_node = nxt_node;
	}



		delete node_to_delete;
		node_to_delete = NULL;
}

void graph_t::clear_visited_flags()
{
    node_t *temp_node=nodes_list;

    temp_node->visited=false; // dla pierwszego wezla

     while(temp_node->next_node)
    {
        temp_node=temp_node->next_node;
        temp_node->visited=false;
    }
}

int graph_t::count_nodes()
{
    node_t *temp_node=nodes_list;
    int nodes_number=1;
    if(temp_node==0) nodes_number=0;
        else
         {
            while(temp_node->next_node)
            {
                temp_node=temp_node->next_node;
                nodes_number++;
            }
         }

         return nodes_number;
}

bool graph_t::search_edges(node_t *parent_node,node_t *&child_node, edge_t *&start_edge)
{
    bool edges_end=false;

    while(start_edge->left_node!=parent_node && start_edge->right_node!=parent_node)
    {
        start_edge=start_edge->next_edge;

        if(start_edge->next_edge==0)
        {
            edges_end=true;
            break;
        }
    }

    if(start_edge->left_node==parent_node) child_node=start_edge->right_node;
        else if (start_edge->right_node==parent_node) child_node=start_edge->left_node;

        return edges_end;

      //pamietac o kasowaniu wskaznika start_edge
}

/*
void graph_t::give_color(node_t *start_node)
{
   node_t *temp_node=parent;
   edge_t *start_edge=temp_node->edges;
   int proposed_color=0;
   bool found_color=false;

   while(!found_color)
   {

      while(!found_color && temp_node->edges->next_edge!=NULL) //jesli nie znaleziono jeszcze koloru albo nie skonczyla sie liczba krawedzi
      {
        found_color=true;
         cout<<"CHECKING "<<temp_node->edges->connected_node->number<<endl;
          if(proposed_color==temp_node->edges->connected_node->color)
          {
              found_color=false;
              cout<<"COLOR "<<proposed_color<<" FOUND IN "<<temp_node->edges->connected_node->number<<endl;
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

*/

void graph_t::paint_graph(node_t *start_node) //jako pierwszy parametr podajemy wezel, od ktorego zaczynamy
{

    bool entering_new_node=true;
    int nodes_amount=count_nodes();
    int checked_nodes_amount=0;

    node_t *temp_node=start_node;
    node_t *child_node;
    node_t *bufor_node;
    edge_t *start_edge;

    clear_visited_flags();

        while(checked_nodes_amount<nodes_amount)
        {
                entering_new_node=false;

                 if(!temp_node->visited)
                {
                    checked_nodes_amount++; //zabezpieczebie zeby sie nie dodalo kilka razy
                    temp_node->visited=true;
                }

                // if(checked_nodes_amount==nodes_amount) break;

                //give_color(temp_node);

                while(!search_edges(temp_node, child_node, start_edge))
                 {
                     if(!child_node->visited) // jesli nie odwiedzono jeszcze wezla child_node
                        {
                            entering_new_node=true;
                            break;
                        }
                 }

               if(entering_new_node) // jesli odnazliono jakis nieodwiedzony wezel
               {
                   cout<<"GOING FROM "<<temp_node->number<<" TO "<<child_node->number<<endl;
                   bufor_node=temp_node;
                   temp_node=child_node;
                   temp_node->return_node=bufor_node;
               }
                    else
                    {                                //UWAGA - nie dziala jesli jestesmy w poczatkowym wezle bo return_node nie jest okreslony
                        cout<<"RETURN TO "<<temp_node->return_node->number<<endl;
                        temp_node=temp_node->return_node; // powracamy do wezla, z ktorego przyszlismy
                    }

                    start_edge=edges_list;
        }

}


int main()
{
	graph_t *graph = new graph_t;
	graph->add_nodes(5);
	graph->add_edge(graph->get_node(1), graph->get_node(2));
	graph->add_edge(graph->get_node(1), graph->get_node(4));
	graph->add_edge(graph->get_node(4), graph->get_node(5));
	graph->add_edge(graph->get_node(4), graph->get_node(3));
	graph->add_edge(graph->get_node(2), graph->get_node(3));

	graph->draw();

	//graph->delete_edge(graph->get_node(1),graph->get_node(2));
	graph->delete_node(2);
	cout<<endl;
	graph->draw();
	delete graph;

}
