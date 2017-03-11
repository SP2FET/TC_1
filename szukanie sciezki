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
