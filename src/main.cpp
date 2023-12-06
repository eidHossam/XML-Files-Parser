#include <iostream>
#include <string.h>
#include <fstream>
#include <bits/stdc++.h> 
#include <stack>
#include <queue>
#include <list>
#include <forward_list>
#include "tree.h"

using namespace std;



int main()
{
    ifstream _xml_file("shebl/sample.xml");

    string _xml_data,tmp;
    if( _xml_file.is_open())
    {
        while (getline(_xml_file,tmp))
        {
            _xml_data=_xml_data+tmp+'\n';
        }
    }

    cout << "Done!." << endl;
    return 0;
}