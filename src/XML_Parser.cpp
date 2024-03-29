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
 * @brief Default constructor of the class.
 * 
 */
XML_Parser::XML_Parser(){}

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
    
    // Close the input file
    _xml_file.close();

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

void XML_Parser::printXML(TreeNode* node) {
    for (int i = 0; i < node->_node_level; ++i) {
        formated_xml_data += "    "; // 4 spaces for each level of node->_node_level
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
            printXML(child);
        }
        for (int i = 0; i < node->_node_level; ++i) {
            formated_xml_data += "    ";
        }
    }

    formated_xml_data += "</" + node->_tag_name + ">\n";
}

/**
  * @}
  */

/** @defgroup Class public functions defenition
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
 * @return vector<string>:List containg all the errors.  
 */
vector<string> XML_Parser::highlight_errors()
{
    vector<string> errors;

    // if the file doesn't have errors then return 
    if (!has_errors())
    {
        return errors;
    }

    /* If we didn't parse the file yet then parse it */
    if (original_xml_data == "")
    {
        get_formatted_xml_data();
    }

    bool leaveNode = false;

    string tmp;
    int tag_count = 1; // Start counting from 1

    stack<string> tags; /* Save the opening tags in the stack to check the consistency */
    string closing_tag;

    stringstream stream(original_xml_data);
    while (getline(stream, tmp, '<'))
    {
        trim(tmp);
        size_t closingBracketPos = tmp.find('>');

        if (closingBracketPos != string::npos)
        {
            if (tmp[0] != '/') // Start tag
            {
                if (leaveNode)
                {
                    /* Missing closing tag */
                    errors.push_back("Missing closing tag \"" + tags.top() + "\" at tag number " +
                                     to_string(tag_count));
                    tags.pop();
                    leaveNode = false;
                }
                string tag_name = tmp.substr(0, closingBracketPos); // Remove the angle brackets
                tags.push(tag_name);

                /* Check if this is a leaveNode node by checking if it contains data */
                string tagData = tmp.substr(closingBracketPos + 1, tmp.length() - closingBracketPos);
                if (!tagData.empty())
                {
                    leaveNode = true;
                }
            }
            else // End tag
            {
                string tagName = tmp.substr(1, closingBracketPos - 1); // Remove the angle brackets

                if (tags.empty())
                {
                    /* Missing opening tag */
                    errors.push_back("Missing opening tag \"" + tagName + "\" at tag number " +
                                     to_string(tag_count++));
                }
                else if (tagName != tags.top())
                {
                    if (leaveNode)
                    {
                        errors.push_back("Mismatch closing tag \"" + tags.top() + "\" at tag number " +
                                         to_string(tag_count++));
                    }
                    else
                    {
                        while (tagName != tags.top())
                        {
                            errors.push_back("Missing closing tag \"" + tags.top() + "\" at tag number " +
                                             to_string(tag_count++));

                            tags.pop();

                            if (tags.empty())
                            {
                                /* Missing opening tag */
                                errors.push_back("Missing opening tag \"" + tagName + "\" at tag number " +
                                                 to_string(tag_count++));
                                break;
                            }
                        }
                    }
                }

                if (!tags.empty())
                {
                    tags.pop();
                }
                leaveNode = false;
            }
            tag_count++;
        }
    }

    while (!tags.empty())
    {
        errors.push_back("Missing closing tag \"" + tags.top() + "\" at tag number " +
                         to_string(tag_count++));

        tags.pop();
    }

    return errors;
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
    string xml_data, tmp;
    
    stack<string> tags; /*Save the opening tags in the stack to check the consistency*/
    stringstream stream(original_xml_data);
    
    while (getline(stream,tmp, '<'))
    {
        trim(tmp);
        size_t closingBracketPos = tmp.find('>');

        if(closingBracketPos != string::npos)
        {
            if(tmp[0] != '/') // Start tag
            {                
                /*Put the start tag in the line*/
                string tagName = tmp.substr(0, closingBracketPos);
                tags.push(tagName);
            }
            else // End tag
            {
                string tagName = tmp.substr(1, closingBracketPos - 1);
                
                if(tagName == tags.top())
                /*If the type of the opening tag doesn't match the type of the closing tag then there is an error*/
                {
                    tags.pop();
                }else{
                    error_flag = true;
                    break;
                }
            } 
        }
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
    if (fixed_xml_data != "")
    {
        return fixed_xml_data;
    }

    // if the file doesn't have errors then return
    if (!has_errors())
    {
        fixed_xml_data = original_xml_data;
        return fixed_xml_data;
    }

    /* If we didn't parse the file yet then parse it */
    if (original_xml_data == "")
    {
        get_formatted_xml_data();
    }

    bool leaveNode = false;

    string xml_data, tmp;

    stack<string> tags; /* Save the opening tags in the stack to check the consistency */
    stringstream stream(original_xml_data);

    while (getline(stream, tmp, '<'))
    {
        trim(tmp);

        size_t closingBracketPos = tmp.find('>');

        if (closingBracketPos != string::npos)
        {
            if (tmp[0] != '/') // Start tag
            {
                if (leaveNode)
                {
                    /* Missing closing tag */
                    xml_data += "</" + tags.top() + ">";
                    tags.pop();
                    leaveNode = false;
                }

                /* Put the start tag in the line */
                string tagName = tmp.substr(0, closingBracketPos);
                xml_data += "<" + tagName + ">";
                tags.push(tagName);

                /* Check if this is a leaveNode node by checking if it contains data */
                string tagData = tmp.substr(closingBracketPos + 1, tmp.length() - closingBracketPos);
                if (!tagData.empty())
                {
                    leaveNode = true;
                    xml_data += tagData;
                }
            }
            else // End tag
            {
                string endTagName = tmp.substr(1, closingBracketPos - 1);
                if (!tags.empty())
                {
                    if (endTagName != tags.top())
                    {
                        /* Missing opening tag, add it */
                        xml_data += "<" + endTagName + ">";
                        tags.push(endTagName);
                    }
                    else
                    {
                        xml_data += "</" + tags.top() + ">";
                        tags.pop();
                        leaveNode = false;
                    }
                }
                else
                {
                    /* Missing opening tag, add it */
                    xml_data += "<" + endTagName + ">";
                    tags.push(endTagName);
                }
            }
        }
    }

    /* Check if there are opening tags without closing tags and fix them */
    while (!tags.empty())
    {
        xml_data += "</" + tags.top() + ">";
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

    printXML(file_tree->root);
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

    string tmp;
    istringstream stream(fixed_xml_data); /*Convert the string into a stream to read it line by line*/

    while(getline(stream, tmp, '<'))
    {
        trim(tmp);
        
        // Extract tag name
        size_t closingBracketPos = tmp.find('>');

        if (closingBracketPos != string::npos) 
        {

            // Check if it's an opening tag
            if (tmp[0] != '/') {
                string tagName = tmp.substr(0, closingBracketPos);
                string tagData = tmp.substr(closingBracketPos + 1, tmp.length() - closingBracketPos);

                if(currentNode == NULL) // If there is no current node, this is the root
                {
                    currentNode = TreeNode::GetNewNode(tagName, tagData);
                    file_tree->root = currentNode;
                }
                else // Otherwise, this is a child node
                {
                    file_tree->InsertChild(currentNode,tagName , tagData);
                    currentNode = currentNode->children.back();
                }

                currentNode->_node_level = node_level++;

            } else {
                // It's a closing tag, move back to the parent
                node_level--;
                currentNode = currentNode->parent;
            }
        }
    }
    return file_tree;
}

void XML_Parser::findPosts(TreeNode* node, const string& word, vector<string>& posts) {
    static string body;
    static bool found_post = false;
    if (node == NULL)
        return;

    if (node->_tag_name == "body") 
    {
        found_post = false;
        body = node->_tag_data;
        string lower_case_body = body;
        transform(lower_case_body.begin(), lower_case_body.end(), lower_case_body.begin(), ::tolower);

        if(lower_case_body.find(word) != string::npos)
        {
            posts.push_back(body);
            found_post = true;
        }
    }else if(node->_tag_name == "topic")
    {
        string data = node->_tag_data;
        string lower_case_data = data;
        transform(lower_case_data.begin(), lower_case_data.end(), lower_case_data.begin(), ::tolower);

        if(!found_post && lower_case_data.find(word) != string::npos)
        {
            posts.push_back(body);
            found_post = true;
        }
    }
    for (auto child : node->children) {
        findPosts(child, word, posts);
    }
}

vector<string> XML_Parser::findPosts(const string& word) {
    vector<string> posts;

    build_xml_tree();
    
    string lower_case_word = word;
    transform(lower_case_word.begin(), lower_case_word.end(), lower_case_word.begin(), ::tolower);

    findPosts(this->file_tree->root, lower_case_word, posts);
    return posts;
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

