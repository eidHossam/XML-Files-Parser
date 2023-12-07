#include "XML_Parser.h"

XML_Parser::XML_Parser() {
    original_xml_data = "";
    fixed_xml_data = "";
}

string XML_Parser::get_xml_data(string file_location) {

    ifstream _xml_file(file_location);

    string _xml_data, tmp;
    if (_xml_file.is_open()) {
        while (getline(_xml_file, tmp)) 
        {
            _xml_data = _xml_data + tmp + '\n';
        }
    }

    original_xml_data = _xml_data;
    return _xml_data;
}

bool XML_Parser::has_errors(string data) 
{
    bool error_flag = false;
    
    stack<string> tags;

    regex _tag_regex("<([^<>]+)>");
    
    sregex_iterator _tag_iterator(data.begin(),data.end(),_tag_regex);
    sregex_iterator _endtag_iterator; 

    while (_tag_iterator !=_endtag_iterator ) {
        smatch match = *_tag_iterator;
       
        string tag = match.str();

        // Check if this is a start tag or an end tag
        if(tag[1] != '/') // Start tag
        {
            string tag_name = tag.substr(1, tag.size() - 2); // Remove the angle brackets
            tags.push(tag_name);
        }
        else // End tag
        {
            string tag_name = tag.substr(2, tag.size() - 3); // Remove the angle brackets
            
            /*If the type of the opening tag doesn't match the type of the closing tag then there is an error*/
            if(tag_name == tags.top())
            {
                tags.pop();
            }else{
                error_flag = true;
                break;
            }
            
        }

        ++_tag_iterator;
    }

    return error_flag; 
}

void trim(string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first != std::string::npos && last != std::string::npos)
        str = str.substr(first, last - first + 1);
    else
        str.clear();
}

string XML_Parser::extract_data_field(string line)
{ 
    string data_field = "";

    trim(line);

    int data_start_index = line.find_first_of('>') + 1;
    int data_end_index = line.find_last_of("</") - 1;

    /*no tags were found*/
    if(data_start_index == string::npos && data_end_index == string::npos)
    {
        data_field = line;

    }else if(data_end_index == string::npos){
        data_field = line.substr(data_start_index, line.size() - data_start_index);

    }else{
        data_field = line.substr(data_start_index, (data_end_index - data_start_index));
    }
    
    return data_field;
}

string XML_Parser::fix_xml_data(string file_location) 
{ 
    /*Open the XML file*/
    ifstream _xml_file(file_location);

    bool leaveNode = false;
    
    string xml_data, tmp;
    
    regex _tag_regex("<([^<>]+)>");
    stack<string> tags; /*Save the opening tags in the stack to check the consistency*/

    if( _xml_file.is_open())
    {
        while (getline(_xml_file,tmp))
        {
            sregex_iterator _tag_iterator(tmp.begin(),tmp.end(),_tag_regex);
            sregex_iterator _endtag_iterator;
            
            /*If there is no tags then all of the line is data*/
            if(_tag_iterator == _endtag_iterator && !tmp.empty())
            {
                trim(tmp);
                xml_data += tmp;
                leaveNode = true;
            }

            while(_tag_iterator != _endtag_iterator)
            {
                smatch match = *_tag_iterator;
                string tag = match.str();

                if(tag[1] != '/') // Start tag
                {
                    if(leaveNode)
                    {
                        /*Missing closing tag*/
                        xml_data += "</" + tags.top() + ">"; 
                        tags.pop();
                        leaveNode = false;
                    }

                    /*Put the start tag in the line*/
                    xml_data += "\n" + match.str();
                    
                    string tag_name = tag.substr(1, tag.size() - 2); // Remove the angle brackets
                    tags.push(tag_name);

                    /*Check if this a leaveNode node by checking if it contains data*/
                    string data_field = extract_data_field(tmp);

                    if(!data_field.empty())
                    {
                        leaveNode = true;
                        xml_data += data_field;
                    }
                }
                else // End tag
                {
                    /*Added to be more readable can be deleted*/
                    if(!leaveNode)
                    {
                        xml_data += "\n";
                    }

                    xml_data += "</" + tags.top() + ">";

                    tags.pop();
                    leaveNode = false;
                }                
                ++_tag_iterator;
            }
        }
    }
    
    /*Check if there opening tags without closing tags and fix them*/
    while(!tags.empty())
    {
        xml_data += "\n</" + tags.top() + ">";
        tags.pop();
    }

    fixed_xml_data = xml_data;
    return fixed_xml_data;
}

XML_Tree XML_Parser::check_consistency(string data)
{    
    XML_Tree tree;
    TreeNode* currentNode = NULL;

    stack<string> tags;
    regex _tag_regex("<([^<>]+)>");

    sregex_iterator _tag_iterator(data.begin(),data.end(),_tag_regex);
    sregex_iterator _endtag_iterator; 

    while (_tag_iterator !=_endtag_iterator ) {
        smatch match = *_tag_iterator;
       
        string tag = match.str();

        // Check if this is a start tag or an end tag
        if(tag[1] != '/') // Start tag
        {
            string tag_name = tag.substr(1, tag.size() - 2); // Remove the angle brackets
            tags.push(tag_name);

            if(currentNode == NULL) // If there is no current node, this is the root
            {
                tree.InsertRoot(tag, "");
                currentNode = tree.root;
            }
            else // Otherwise, this is a child node
            {
                tree.InsertChild(currentNode, tag, "");
                currentNode = currentNode->children.back();
            }
        }
        else // End tag
        {
            string tag_name = tag.substr(2, tag.size() - 3); // Remove the angle brackets
            /*If the type of the opening tag doesn't match the type of the closing tag then there is an error*/
            cout << tag_name << " " <<  tags.top() << endl;
            if(tag_name == tags.top())
            {
                tags.pop();
            }
            
            currentNode = currentNode->parent; // Move up to the parent node            
        }

        ++_tag_iterator;
    }
    return tree;
}


