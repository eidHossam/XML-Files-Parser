#pragma once
#include <bits/stdc++.h> 
#include "tree.h"
#include <sstream>

using namespace std;

class XML_Parser
{
private:
  /** @defgroup Private data members of the XML parser class
    * @{
    */
    string file_location;       /*The location of the xml file to parsed*/
    string original_xml_data;   /*The xml data as present in the xml file (might be raw or formatted)*/
    string fixed_xml_data;      /*The xml data after fixing any inconsistencies (if there is any)*/
    string formated_xml_data;   /*The xml data after formatting it*/

    XML_Tree* file_tree;        /*The xml data represented as a tree*/

  /**
    * @}
    */

    /** @defgroup Private helping functions.
      * @{
      */
    string get_xml_data( int formatting);
    
    void trim(string& str);
    
    string extract_data_field(string line);

    void printXML(TreeNode* node, int depth);
    /**
      * @}
      */ 

public:

    /**
     * @brief Constructor of the XML parser class.
     * 
     * @param file_location: string of the file location to be parsed.
     */
    XML_Parser(string file_location);

    /**
     * @brief Function to return the XML data in the given file without any formatting(spaces - new lines).
     * 
     * @return string: The xml data.
     */
    string get_raw_xml_data();

    /**
     * @brief Function to return the XML data in the given file with formatting(spaces - new lines).
     * 
     * @return string: The xml data. 
     */
    string get_formatted_xml_data();

    /**
     * @brief This function checks if the given file has any inconsistencies in the tags.
     * 
     * @return true: If the files contains any errors. 
     * @return false: If the files is error free.
     */
    bool has_errors();

    /**
     * @brief Function to highlight the exact place of the error (if there is one) by typing "ERROR" where is one.
     * 
     * @return string: The xml data.  
     */
    string highlight_errors();

    /**
     * @brief Function to fix the errors present in the XML file.
     * 
     * @return string: The xml data.  
     */
    string fix_xml_data();

    /**
     * @brief Function to fix the formatting of the file(indentation - new lines) for the file to be more readable.
     * 
     * @return string: The formatted xml data.  
     */
    string xml_format();

    /**
     * @brief Function to convert the xml data into a tree.
     * 
     * @return XML_Tree*: a pointer to the tree object.
     */
    XML_Tree* build_xml_tree();

/** @defgroup Getters
  * @{
  */
    string get_original_xml_data();

    string get_fixed_xml_data();
/**
  * @}
  */
};

