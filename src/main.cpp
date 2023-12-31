#include "tree.h"
#include "XML_Parser.h"


using namespace std;

int main()
{
    string _xml_data;
    XML_Parser parser("src/sample.xml");

    _xml_data = parser.get_raw_xml_data();
    cout << _xml_data << endl;

    vector<string> vec = parser.highlight_errors();

    for(string s : vec)
    {
        cout << s << "\n";
    }


    _xml_data = parser.get_fixed_xml_data();
    cout << _xml_data << endl;

    _xml_data = parser.xml_format();
    cout << _xml_data << endl;

    
    return 0;
}