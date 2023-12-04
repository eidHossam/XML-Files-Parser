#include<iostream>
#include<string.h>
#include <fstream>
#include<bits/stdc++.h> 
#include <stack>
#include <queue>
#include <list>
#include <forward_list>

using namespace std;
int main()
{
    
    ifstream _xml_file("C:\\Users\\youssef\\Desktop\\programing\\DS_c++\\Project\\sample.xml");

    string _xml_data,tmp;
    if( _xml_file.is_open())
    {
        while (getline(_xml_file,tmp))
        {
           
            _xml_data=_xml_data+tmp; //_xml_data.append(tmp);
        }
    }
    //_xml_data.erase(std::remove_if(_xml_data.begin(), _xml_data.end(), "\t"), _xml_data.end());
    
    regex _tag_regex("<([^<>]+)>");
    sregex_iterator _tag_iterator(_xml_data.begin(),_xml_data.end(),_tag_regex);
    sregex_iterator _endtag_iterator; 
   
    //"\\(([^)]+)\\)"
    while (_tag_iterator !=_endtag_iterator ) {
        std::smatch match = *_tag_iterator;
        //Here
        cout<<match.str()<<endl;
        ++_tag_iterator;
    }

    
    // regex _info_regex( "<(topic|id|name|body)>(.*?)</(topic|id|name|body)>" );

    // sregex_iterator _info_iterator(_xml_data.begin(),_xml_data.end(),_info_regex);
    // sregex_iterator _endinfo_iterator; 
    // while (_info_iterator !=_endinfo_iterator ) {
    //     std::smatch match = *_info_iterator;
    //     cout<<match.str()<<endl;
    //     ++_info_iterator;
    // }

    return 0;
}
