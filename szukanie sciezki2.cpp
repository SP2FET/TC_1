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
	return_node = NULL;
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
	bool painting_donable; // wskazuje, czy da sie pokolorowac graf

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
	void    give_color(node_t *start_node);
	bool    search_edges(node_t *parent_node, node_t *&child_node, edge_t *&start_edge);

} ;

graph_t::graph_t()
{
	edges_list = NULL;
	nodes_list = NULL;
	painting_donable=false;
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


	delete_edge(left, right);

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

	system("cls");
	if( count_nodes() == 0)
	{
		cout<<endl<<endl<<"FIRST CREATE NODE!";
		cin.sync();
		cin.get();
		return;
	}

	if(temp_node == NULL || edges_list == NULL) return;


	cout<<endl<<endl;
	do
	{
		cout<<"node "<<temp_node->number<<" (color ";

		if(temp_node->color && painting_donable)  cout<<temp_node->color<<") is connected with: ";
		  else cout<<"is undefined"<<") is connected with: ";
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
	cin.sync();
	cin.get();

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
    char test;

    while(start_edge->left_node!=parent_node && start_edge->right_node!=parent_node)
    {
        if(start_edge->next_edge==0)
        {
        //    cout<<"END OF EDGE LIST"<<endl;
            edges_end=true;                    // jak to sie ustawi to juz na pewno zadna krawedz sie nie znajdzie
            break;
        }
         else   start_edge=start_edge->next_edge;
    }

    if(!edges_end)
    {
        if(start_edge->left_node==parent_node)   child_node=start_edge->right_node;
        else if(start_edge->right_node==parent_node)  child_node=start_edge->left_node;

        //cout<<"TESTED EDGE FROM "<<parent_node->number<<" TO "<<child_node->number<<endl;
    }

        return edges_end;

}

void add_node_dialog(graph_t *graph);
void add_multiple_nodes_dialog(graph_t *graph);
void add_edge_dialog(graph_t *graph);
void delete_node_dialog(graph_t *graph);
void delete_edge_dialog(graph_t *graph);
void paint_dialog(graph_t *graph);


void graph_t::give_color(node_t *start_node)
{
   node_t *temp_node=start_node;
   node_t *child_node;
   edge_t *start_edge=edges_list;
   int proposed_color=1;
   bool found_color=false;
   bool painting_donable=true;

   while(!found_color)
   {
      // cout<<endl<<"GIVING COLOR"<<endl<<endl;
       found_color=true;                        // zakladam, ze znajde kolor
      while(found_color && !search_edges(temp_node,child_node,start_edge)) //jesli nie znaleziono jeszcze koloru albo nie skonczyla sie liczba krawedzi
      {

          if(proposed_color==child_node->color)
          {
              found_color=false;  // jesli proponowany kolor jest w jednym z sasiadujacych wezlow
           //   cout<<"COLOR "<<proposed_color<<" FOUND IN "<<child_node->number<<endl;
              break;
          }

            else if(start_edge->next_edge==0)
             {
            //    cout<<"END OF EDGE LIST2"<<endl;
                break;
             }

            else  start_edge=start_edge->next_edge;
      }
     if(!found_color) proposed_color++;
     start_edge=edges_list;
   }

     //cout<<endl<<"END OF GIVING COLOR"<<endl<<endl;

   temp_node->color=proposed_color;
  // cout<<"Node "<<temp_node->number<<" has given "<<temp_node->color<<" color"<<endl;
}


void graph_t::paint_graph(node_t *start_node) //jako pierwszy parametr podajemy wezel, od ktorego zaczynamy
{

    bool entering_new_node=true;
    painting_donable=true;
    int checked_nodes_amount=0;

    node_t *temp_node=start_node;
    node_t *child_node;
    node_t *bufor_node;
    edge_t *start_edge=edges_list;

    clear_visited_flags();
    int nodes_amount=count_nodes();

        while(checked_nodes_amount<nodes_amount)
        {
                entering_new_node=false;
                start_edge=edges_list;

                 if(!temp_node->visited)
                {
                    checked_nodes_amount++; //zabezpieczebie zeby sie nie dodalo kilka razy
                    temp_node->visited=true;
                    give_color(temp_node);
                }



                while(!search_edges(temp_node, child_node, start_edge))
                 {
                     if(!child_node->visited) // jesli nie odwiedzono jeszcze wezla child_node
                        {
                            entering_new_node=true;
                            break;
                        }

                        else if(start_edge->next_edge==0)
                            {
                                //cout<<"END OF EDGE LIST2"<<endl;
                                break;
                            }

                           else  start_edge=start_edge->next_edge;
                 }

               if(entering_new_node) // jesli odnazliono jakis nieodwiedzony wezel
               {
                  // cout<<endl<<"GOING FROM "<<temp_node->number<<" TO "<<child_node->number<<endl<<endl;
                   bufor_node=temp_node;
                   temp_node=child_node;
                   temp_node->return_node=bufor_node;
               }
                    else if(temp_node->return_node==0)  //nie przechodzimy do nowego wezla a poprzedni nie istnieje -  nie da sie pokolorowac grafu
                     {
                         cout<<endl<<endl<<"CANNOT GO THROUGH THE WHOLE GRAPH!"<<endl;;
                         painting_donable=false;
                         break;
                     }

                    else
                    {
                        //cout<<endl<<"RETURN TO "<<temp_node->return_node->number<<endl<<endl;
                        temp_node=temp_node->return_node; // powracamy do wezla, z ktorego przyszlismy
                    }

        }

}


void show_menu(graph_t *graph)
{
	char c;
	system("cls");
	cout<<endl<<endl;
	cout<<"1. Add new node"<<endl;
	cout<<"2. Add multiple nodes"<<endl;
	cout<<"3. Add new edge"<<endl;
	cout<<"4. Delete node"<<endl;
	cout<<"5. Delete edge"<<endl;
	cout<<"--------------------------------------------------------"<<endl;
	cout<<"6. Color up graph (only when there're no orphaned nodes')"<<endl;
	cout<<"7. Display nodes and edges"<<endl;
	cout<<">";
	cin>>c;

	switch(c)
	{
		case '1':
				 add_node_dialog(graph);
				 break;
		case '2':
				 add_multiple_nodes_dialog(graph);
				 break;
		case '3':
				 add_edge_dialog(graph);
				 break;
		case '4':
				 delete_node_dialog(graph);
				 break;
		case '5':
				 delete_edge_dialog(graph);
				 break;
		case '6':
				 paint_dialog(graph);
				 show_menu(graph);

		case '7':
				 graph->draw();


		default: show_menu(graph);
	}

}

void add_node_dialog(graph_t *graph)
{
	char c, upper_c;
	system("cls");
	cout<<"ADDING NEW NODE"<<endl<<endl;
	cout<<"Do you really want to add new node? (y/n)"<<endl;
	cout<<">";
	cin>>c;
	upper_c = toupper(c);

	if(upper_c == 'Y')
	{
		graph->add_node();
		cout<<endl<<"SUCCESSFULLY ADDED NODE "<<graph->count_nodes()<<" !";
		cin.sync();
		cin.get();

	}
	show_menu(graph);
}

void delete_node_dialog(graph_t *graph)
{
	int nodes_amount = graph->count_nodes();
	int node_to_delete;
	char c, upper_c;
	system("cls");
	cout<<"DELETING NODE"<<endl<<endl;
	if(nodes_amount == 0)
	{
		cout<<"FIRST CREATE NODE!";
		cin.sync();
		cin.get();
		show_menu(graph);
	}
	cout<<"Enter node to delete: (1 - "<<nodes_amount<<")"<<endl;
	cout<<">";
	cin>>node_to_delete;
	if(node_to_delete > nodes_amount)
	{
		cout<<endl<<"ENTER ANOTHER NODE!";
		delete_node_dialog(graph);
	}
	cout<<endl;
	cout<<"Do you really want to delete node "<<node_to_delete<<"? (y/n)"<<endl;
	cout<<">";
	cin>>c;
	upper_c = toupper(c);

	if(upper_c == 'Y')
	{
		graph->delete_node(node_to_delete);
		cout<<endl<<"SUCCESSFULLY DELETED NODE!";
		cin.sync();
		cin.get();

	}
	show_menu(graph);
}

void delete_edge_dialog(graph_t *graph)
{
	int first, second;
	int nodes_amount = graph->count_nodes();
	char c, upper_c;
	system("cls");
	cout<<"DELETING EDGE"<<endl<<endl;
	if(nodes_amount == 0)
	{
		cout<<"FIRST CREATE NODE!";
		cin.sync();
		cin.get();
		show_menu(graph);
	}
	cout<<"Enter first node of edge"<<endl;
	cout<<">";
	cin>>first;
	cout<<endl;
	cout<<"Enter second node of edge"<<endl;
	cout<<">";
	cin>>second;

	if(first == second || first > nodes_amount || second > nodes_amount)
	{
		cout<<endl<<"ENTER ANOTHER NODE!";
		delete_edge_dialog(graph);
	}


	cout<<"Do you really want to delete edge between "<<first<<" and "<<second<<" node? (y/n)"<<endl;
	cout<<">";
	cin>>c;
	upper_c = toupper(c);

	if(upper_c == 'Y')
	{
		graph->delete_edge(graph->get_node(first),graph->get_node(second) );
		cout<<endl<<"SUCCESSFULLY DELETED NODE!";
		cin.sync();
		cin.get();

	}
	show_menu(graph);
}

void add_multiple_nodes_dialog(graph_t *graph)
{
	int amount;
	int act_amount = graph->count_nodes();

	system("cls");
	cout<<"ADDING MULTIPLE NODES"<<endl<<endl;
	cout<<"Enter amount of nodes to add"<<endl;
	cout<<">";
	cin>>amount;

	graph->add_nodes(amount);
	if(act_amount == 0) act_amount = 1;
		cout<<endl<<"SUCCESSFULLY ADDED "<<amount<<" NODES! ("<<act_amount<<" - "<<graph->count_nodes()<<")";
		cin.sync();
		cin.get();


	show_menu(graph);
}

void add_edge_dialog(graph_t *graph)
{
	int nodes_amount = graph->count_nodes();
	int first, second;
	system("cls");
	cout<<"ADDING NEW EDGE"<<endl<<endl;
	if(nodes_amount == 0)
	{
		cout<<"FIRST CREATE NODE!";
		cin.sync();
		cin.get();
		show_menu(graph);
	}
	cout<<"Enter first node: (1 - "<<nodes_amount<<")"<<endl;
	cout<<">";
	cin>>first;
	cout<<endl;
	cout<<"Enter second node: (1 - "<<nodes_amount<<") \\ "<<first<<endl;
	cout<<">";
	cin>>second;
	if(first == second || first > nodes_amount || second > nodes_amount)
	{
		cout<<endl<<"ENTER ANOTHER NODE!";
		cin.sync();
		cin.get();
		add_edge_dialog(graph);
	}

	graph->add_edge(graph->get_node(first),graph->get_node(second));


		cout<<endl<<"SUCCESSFULLY ADDED EDGE!";
		cin.sync();
		cin.get();


	show_menu(graph);
}

void paint_dialog(graph_t *graph)
{
	int node_number;
	int nodes_amount = graph->count_nodes();
	system("cls");
	cout<<"PAINTING GRAPH"<<endl<<endl;
	if(nodes_amount == 0)
	{
		cout<<"FIRST CREATE NODE!";
		cin.sync();
		cin.get();
		show_menu(graph);
	}
	cout<<"Enter node to start painting with: (1 - "<<nodes_amount<<")"<<endl;
	cout<<">";
	cin>>node_number;
	if (node_number > nodes_amount)
	{
		cout<<endl<<"ENTER ANOTHER NODE!";
		cin.sync();
		cin.get();
		paint_dialog(graph);

	}
	graph->paint_graph(graph->get_node(node_number));

	if(graph->painting_donable)cout<<endl<<endl<<"DONE!";
        else cout<<endl<<endl<<"CANNOT PAINT GRAPH BECAUSE OF THE WRONG CONNECTIONS!";

	cin.sync();
	cin.get();
}
int main()
{
	graph_t *graph = new graph_t;
	graph->add_nodes(8);
	graph->add_edge(graph->get_node(1), graph->get_node(2));
	graph->add_edge(graph->get_node(2), graph->get_node(3));
	//graph->add_edge(graph->get_node(3), graph->get_node(4));
	graph->add_edge(graph->get_node(4), graph->get_node(5));
	//graph->add_edge(graph->get_node(5), graph->get_node(6));
	//graph->add_edge(graph->get_node(6), graph->get_node(7));
	graph->add_edge(graph->get_node(7), graph->get_node(8));
	graph->add_edge(graph->get_node(8), graph->get_node(1));

	//graph->add_edge(graph->get_node(1), graph->get_node(4));
	//graph->add_edge(graph->get_node(1), graph->get_node(5));
	//graph->add_edge(graph->get_node(2), graph->get_node(6));
	//graph->add_edge(graph->get_node(2), graph->get_node(8));
	//graph->add_edge(graph->get_node(5), graph->get_node(8));
  //  graph->add_edge(graph->get_node(5), graph->get_node(7));
	//graph->add_edge(graph->get_node(5), graph->get_node(3));
	//graph->add_edge(graph->get_node(5), graph->get_node(2));
//
//
//
//
//
//
//	graph->draw();
//
//	graph->paint_graph(graph->nodes_list);
//
//	//graph->delete_edge(graph->get_node(8),graph->get_node(5));
//	//graph->delete_node(10);

	show_menu(graph);
//	cout<<endl;
//	graph->draw();
	delete graph;

}
