#include <iostream>

using namespace std;

struct connection
{
 connection *next;
 node *child;
};

struct node
{
 short name;
 bool visited=false;   // uzywane tylko przy przeszukiwaniu listy
 node *previos_node;  // uzywane tylko przy przeszukiwaniu listy
 connection *actual_connection;
};

bool search_node(node *next_node, node *&found_node, short node_name) //jako pierwszy parametr podajemy wezel, od ktorego zaczynamy
{
    bool wanted_node_exists=false;
    node *bufor;

        while(//tu nie wiem co, trzeba jakos sprawdzic czy nie sprawdzilo sie juz wszystkich wezlow)
        {
            while(next_node->actual_connections->child.visited) // dopoki nastepny wezel z listy polaczen wezel zostal odwiedzony
            {
                if(next_node->actual_connections->next==NULL) //jesli dotarlismy do ostatniego polaczenia i bylo odwiedzone - wszystkie drogi juz odwiedzilismy
                {
                    next_node=previous_node; // powracamy do wezla, z ktorego przyszlismy
                    break;
                }

                next_node->actual_connection=next_node->actual_connection->next; //sprawdzamy nastepne polaczenie
            }

            bufor=next_node;
            next_node=next_node->actual_connection->child; // jesli odnazliono jakis nieodwiedzony wezel
            next_node->previous_node=bufor;

            if(next_node.name!=node_name)
            {
                found_node=next_node;
                wanted_node_exists=true;
            }

            next_node.visited=true;
        }

        return wanted_node_exists;
}


bool add_connection(short child_name, short parent_name)
{
   node *parent;
   node *child;

   if(search_node(parent,parent_name))
    {

    }
     else cout<<"Nie znaleiono wezla-rodzica!"<<endl;

}


int main()
{

 node *first_node=NULL;


    return 0;
}
