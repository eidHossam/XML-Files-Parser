

// // C++ program to demonstrate working of regex_search()
// #include <iostream>
// #include <regex>
// #include<string.h>
// using namespace std;
 
// int main()
// {
//     // Target sequence
//     string s = "I am looking for <GeeksForGeeks> articles <heheh> now it works <isa>";
 
//     // An object of regex for pattern to be searched
//     regex r("<([^<>]+)>");
//     sregex_iterator word_iterator(s.begin(),s.end(),r);
//     sregex_iterator end_iterator; 
//     int count = 0;
//     string  test [100];
//     //"\\(([^)]+)\\)"
//     while (word_iterator !=end_iterator ) {
//         std::smatch match = *word_iterator;
//         auto x=match;
//         cout<<match.str(1)<<endl;
//         count++;
//         ++word_iterator;
//     }
    
//     // flag type for determining the matching behavior
//     // here it is for matches on 'string' objects
//     //smatch m;
 
//     // regex_search() for searching the regex pattern
//     // 'r' in the string 's'. 'm' is flag for determining
//     // matching behavior.
//     //regex_search(s, m, r);
//     //cout << s << endl;
 
//     // for each loop
//     // for (auto x : m)
//     //     cout << x <<m.position()<< "   ????what??? \n";
 
//     // return 0;
// }
#include <iostream>
#include <regex>
#include <string>
using namespace std;

std::vector<std::string> extractTextBetweenBodyTags(const std::string& htmlContent) {
    std::regex bodyRegex("<body>(.*?)</body>");
    std::sregex_iterator iter(htmlContent.begin(), htmlContent.end(), bodyRegex);
    std::sregex_iterator end;

    std::vector<std::string> extractedTexts;

    while (iter != end) {
        std::smatch match = *iter;
        if (match.size() > 1) {
            cout<<match.str(1)<<endl; // Store the text captured between <body> tags
        }
        ++iter;
    }

    return extractedTexts;
}

int main() {
    std::string htmlText = "<body>"
    "First body text..."
   " </body> "
"    Some other content"    
" <body>"
    "Second body text..."
     "</body>"; // Your HTML content here

    std::vector<std::string> extractedTexts = extractTextBetweenBodyTags(htmlText);

    // if (!extractedTexts.empty()) {
    //     std::cout << "Text found between <body> tags:" << std::endl;
    //     for (const std::string& text : extractedTexts) {
    //         std::cout << text << std::endl;
    //     }
    // } else {
    //     std::cout << "No text found between <body> tags." << std::endl;
    // }

    return 0;
}


