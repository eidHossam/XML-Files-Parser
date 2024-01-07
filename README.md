# [CSE331] Data Structures And Algorithms project # 

# Main idea #
This project is a GUI based program used to parse and visualize an XML file representing users in a social network
, Each user has id (unique), name, list of posts, list of followers, And each post has text and a list of topics.

# project description # 

- In this project we will work on some processes on the xml file like :

   1- Reading the xml file by locating it using the GUI or by giving the address of the file and showing the content of it to the user.

   2- Checking the consistency of the xml file.

   3- Detecting and visually showing the errors in 
   the consistency if there is any.
   
   4- The program is also be able to solve the errors. 

   5- Formatting (Prettifying) the XML: the XML file should be well formatted by keeping the 
   indentation for each level.

   6- Converting XML to JSON: JSON (Javascript Object Notation) is another format that is used 
   to represent data as It’s helpful to convert the XML into JSON, especially when using 
   javascript as there’s tons of libraries and tools that use json notation.  

   7- Minifying the XML file: Since spaces and newlines (\n) are actually characters that can 
   increase the size of an XML document. This feature should aim at decreasing the size of 
   an XML file by deleting the whitespaces and indentations.

   8- Compressing the data in the XML file: Decreasing the size of the xml file by compressing it using huffman encoding algorithm.

   9- Decompressing the compressed data to return to 
   its original format.

   10- The user can edit the xml file from within the program.

   11- The ability to undo, redo the changes while editing the xml file.

- In our system the XML file will represent users in a social network
  Each user has id (unique), name, list of posts, list of followers.
  Each post has text and list of topics,so we will : 

    1- represent the users data using the graph data structure: the XML file will represent the 
  users data in a social network (their posts, followers, ...etc). Then we will build a graph relation between the user.

    2- Apply network analysis on the constructed graph: We can 
  extract some important data:

    - who is the most influencer user (has the most followers)

    - who is the most active user (connected to lots of users)

    - the mutual followers between 2 users

    - for each user, suggest a list of users to follow (the followers of his followers)
    
     3- do  Post search: given a specific word or topic, get the posts where this word or topic was 
  mentioned.

- finally we will build qt application to interface with our xml application and to : 

     1- allow the user to choose the XML file that will be used or enter the xml 
     manually in a text area

     2- allow viewing the input XML and the output of each operation as much as 
     possible

     3- allow the user to save the results of the operations to a new file.

# snapshots # 

### Main Window
![Main_window](https://github.com/eidHossam/XML-Files-Parser/assets/106603484/dbc7c103-03c5-41d5-b8ec-bcdf260f16c4)

### Reading file
![Reading_File](https://github.com/eidHossam/XML-Files-Parser/assets/106603484/20ac6449-166c-4422-808d-146ca5396d6a)

### Minifyed file
![Minified](https://github.com/eidHossam/XML-Files-Parser/assets/106603484/fd95cd9b-1482-47aa-ada9-723d1940fdff)

### Network analysis
![Net_analysis](https://github.com/eidHossam/XML-Files-Parser/assets/106603484/909fa015-bbbf-45c9-936a-a4fff7978077)

### Post search
![Post_Search](https://github.com/eidHossam/XML-Files-Parser/assets/106603484/cb4f0f15-8981-4f25-b468-29852effc071)

# setup #
To run this project, you need to download the release zip file. 

# live demo # 
To see live demo for project, follow this link : 
