#include "XML_Parser.h"

/** @defgroup Local DEFINES
  * @{
  */
#define FORMAT_RAW   0
#define FORMAT_PRETTY 1
/**
  * @}
  */


/** @defgroup Class constructors
  * @{
  */

/**
 * @brief Constructor of the XML parser class.
 * 
 * @param file_location: string of the file location to be parsed.
 */
XML_Parser::XML_Parser(string file_location) {
    this->file_location = file_location;
    original_xml_data = "";
    fixed_xml_data = "";
    file_tree = NULL;
}

/**
  * @}
  */


/** @defgroup Class Private Functions
  * @{
  */

string XML_Parser::get_xml_data(int formatting) {

    ifstream _xml_file(file_location);

    string _xml_data, tmp;
    if (_xml_file.is_open()) {
        while (getline(_xml_file, tmp)) 
        {
            if(formatting == FORMAT_RAW)
            {
                trim(tmp);
                _xml_data = _xml_data + tmp;
            }else{
                _xml_data = _xml_data + tmp + "\n";
            }
        }
    }

    original_xml_data = _xml_data;
    return _xml_data;
}

void XML_Parser::trim(string& str) {
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

void XML_Parser::printXML(TreeNode* node, int depth) {
    for (int i = 0; i < depth; ++i) {
        formated_xml_data += "    "; // 4 spaces for each level of depth
    }

    formated_xml_data += "<" + node->_tag_name + ">";
    
    if (!node->_tag_data.empty())
    {
        formated_xml_data += node->_tag_data;
    } else if (!node->children.empty()) 
    {
        formated_xml_data += "\n";
        for (const auto& child : node->children)
        {
            printXML(child, depth + 1);
        }
        for (int i = 0; i < depth; ++i) {
            formated_xml_data += "    ";
        }
    }

    formated_xml_data += "</" + node->_tag_name + ">\n";
}

/**
  * @}
  */

/** @defgroup Class oublic functions defenition
  * @{
  */

/**
* @brief Function to return the XML data in the given file without any formatting(spaces - new lines).
* 
* @return string: The xml data.
*/
string XML_Parser::get_raw_xml_data()
{
    return get_xml_data(FORMAT_RAW);
}

/**
* @brief Function to return the XML data in the given file with formatting(spaces - new lines).
* 
* @return string: The xml data. 
*/
string XML_Parser::get_formatted_xml_data()
{
    return get_xml_data(FORMAT_PRETTY);
}

/**
 * @brief Function to highlight the exact place of the error (if there is one) by typing "ERROR" where is one.
 * 
 * @return string: The xml data.  
 */
string XML_Parser::highlight_errors()
{
    
}

/**
 * @brief This function checks if the given file has any inconsistencies in the tags.
 * 
 * @return true: If the files contains any errors. 
 * @return false: If the files is error free.
 */

bool XML_Parser::has_errors() 
{

    /*If we already fixed the file then no need to check again*/
    if(fixed_xml_data != "")
    {
        return false;
    }

    /*If we didn't parse the file yet then parse it*/
    if(original_xml_data == "")
    {
        get_formatted_xml_data();
    }

    bool error_flag = false;
    
    stack<string> tags;

    regex _tag_regex("<([^<>]+)>");
    
    sregex_iterator _tag_iterator(original_xml_data.begin(),original_xml_data.end(),_tag_regex);
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

/**
 * @brief Function to fix the errors present in the XML file.
 * 
 * @return string: The xml data.  
 */
string XML_Parser::fix_xml_data() 
{ 
    //if the file doesn't have errors then return 
    if(!has_errors())
    {
        fixed_xml_data = original_xml_data;
        return fixed_xml_data;
    }

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

/**
 * @brief Function to fix the formatting of the file(indentation - new lines) for the file to be more readable.
 * 
 * @return string: The formatted xml data.  
 */
string XML_Parser::xml_format() 
{   
    if(formated_xml_data != "")
    {
        return formated_xml_data;
    }
    /*1 - Build the tree */
    build_xml_tree();

    printXML(file_tree->root, 0);
    return formated_xml_data; 
}

/**
 * @brief Function to convert the xml data into a tree.
 * 
 * @return XML_Tree*: a pointer to the tree object.
 */
XML_Tree* XML_Parser::build_xml_tree()
{    
    /*If we already built the tree once don't do it again*/
    if(file_tree)
    {
        return file_tree;
    }

    /*If we didn't parse the file yet then parse it*/
    if(original_xml_data == "")
    {
        get_formatted_xml_data();
    }

    fix_xml_data();

    file_tree = new XML_Tree();
    TreeNode* currentNode = NULL;
    int node_level = 0;

    regex _tag_regex("<([^<>]+)>");


    string tmp;
    istringstream stream(fixed_xml_data); /*Convert the string into a stream to read it line by line*/

    while(getline(stream, tmp))
    {

        sregex_iterator _tag_iterator(tmp.begin(),tmp.end(),_tag_regex);
        sregex_iterator _endtag_iterator; 

        /*If there is no tags then all of the line is data*/
        if(_tag_iterator == _endtag_iterator && !tmp.empty())
        {
            trim(tmp);
            currentNode->_tag_data += tmp;
        }

        while (_tag_iterator !=_endtag_iterator ) {
            smatch match = *_tag_iterator;

            string tag = match.str();

            // Check if this is a start tag or an end tag
            if(tag[1] != '/') // Start tag
            {
                /*Check if this a leaveNode node by checking if it contains data*/
                string data_field = extract_data_field(tmp);
                
                string tag_name = tag.substr(1, tag.size() - 2); // Remove the angle brackets

                if(currentNode == NULL) // If there is no current node, this is the root
                {
                    currentNode = TreeNode::GetNewNode(tag_name, data_field);
                    file_tree->root = currentNode;
                }
                else // Otherwise, this is a child node
                {
                    file_tree->InsertChild(currentNode, tag_name, data_field);
                    currentNode = currentNode->children.back();
                }

                currentNode->_node_level = node_level;

                node_level++;  /*Increment the node level when we encounter an opening tag*/
            }
            else // End tag
            {
                node_level--;
                currentNode = currentNode->parent; // Move up to the parent node            
            }

            ++_tag_iterator;
        }
    }

    return file_tree;
}

/**
  * @}
  */


/** @defgroup Data Members Getters
  * @{
  */
string XML_Parser::get_original_xml_data(){
    /*If we didn't parse the file yet then parse it*/
    if(original_xml_data == "")
    {
        get_formatted_xml_data();
    }

    return original_xml_data;
}

string XML_Parser::get_fixed_xml_data(){
    fix_xml_data();

    return fixed_xml_data; 
}
/**
  * @}
  */
