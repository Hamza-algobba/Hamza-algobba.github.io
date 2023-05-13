#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <map>
#include "avl.h"

using namespace std;




int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum
// of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
Node* newNode(string key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially
                      // added at leaf
    return(node);
}
 
// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}
 
// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left),   
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
Node* insert(Node* node, string key)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));
 
    if(key.compare(node->key)<0)
        node->left = insert(node->left, key);
    else if (key.compare(node->key)>0)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                        height(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
// A utility function to print preorder
// traversal of the tree.
// The function also prints height
// of every node
void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->key<<"\n";
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(Node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

bool case_sensitive_search(string key, Node *node){
   if(node == NULL) {
      return 0;
   }
   if(node->key == key) {
      return 1;
   }
   if(key.compare(node->key)>0)
   {
      return case_sensitive_search(key,node->right);
   }
   else {
      return case_sensitive_search(key,node->left);
   }
}

bool case_insensitive_search(string key, Node *node){
    
    
   if(node == NULL) {
      return 0;
   }
   
    string k = key;
    transform(k.begin(), k.end(), k.begin(), ::toupper);
    string nk = node ->key;
    transform(nk.begin(), nk.end(), nk.begin(), ::toupper);
   if(nk == k) {
      return 1;
   }
   if(k.compare(nk)>0)
   {
      return case_insensitive_search(k,node->right);
   }
   else {
      return case_insensitive_search(k,node->left);
   }
}

vector<string> tokenize(string s, string del)
{
    int start = 0;
    int end = s.find(del);
    vector <string> substrings;
    while (end != -1) {
        substrings.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    substrings.push_back(s.substr(start, end - start));
    
    return substrings;
}









class Website
{
  public:
  string url;
  string file_name;
  int website_ID;
  Node *keywords_root;
  int num_keywords;
  vector<string> external_links;
  
  public:
  
  Website()
  {
      url = "";
      file_name = "";
      keywords_root = NULL;
      num_keywords = 0;
      website_ID = 0;
  }
  
  Website(string u, string fn, Node *k, int nk, int wid)
  {
      url = u;
      file_name = fn;
      num_keywords = nk;
      keywords_root = k;
      website_ID = wid;
  }

  void set_website_ID(int wid)
  {
      website_ID = wid;
  }
  
  void set_num_of_keywords(int nk)
  {
      num_keywords = nk;
  }
  
  void set_url(string u)
  {
      url = u;
  }
  
  void set_file_name(string fn)
  {
      file_name = fn;
  }
  
  void set_keywords(Node *k)
  {
    keywords_root = k;
  }

  int get_num_of_keywords()
  {
      return num_keywords;
  }
  
  string get_url()
  {
      return url;
  }
  
  string get_file_name()
  {
      return file_name;
  }
  
  int get_website_ID()
  {
      return website_ID;
  }

  Node* get_keywords()
  {
      return keywords_root;
  }
  
  
  
  void display_file()
  {
        string myText;
    
        ifstream MyReadFile(file_name);
        
        while (getline (MyReadFile, myText))
        {
            cout << myText<<endl;
        }
        
        MyReadFile.close();
  }
  
  bool search_keywords(string query)
  {
      int size = query.length();
      
      //check if it is in quotations
      if((query[0] == '"') && (query[size - 1] == '"'))
      {
          string raw_query; //removes the quotations and searches for the string as it is
          raw_query.resize(size - 2, ' ');
          for(int i = 0; i<size - 2 ; i++)
          {
              raw_query[i] = query[i+1];
              
          }
          
          return  case_sensitive_search(raw_query, keywords_root);  
          
      }
      
      
      else
      {
          //check for AND operator
          
          if(tokenize(query, " AND ").size() != 1) 
          {
              vector<string> sub_strings = tokenize(query, " AND ");
              for(int i = 0; i<sub_strings.size(); i++)
              {
                  if(!case_insensitive_search(sub_strings[i], keywords_root))
                  {
                      
                      return false;
                  }
              }
              
              return true;
          }
          
          //check for OR operator
          else if(tokenize(query, " OR ").size() != 1)
          {
              vector<string> sub_strings = tokenize(query, " OR ");
              for(int i = 0; i<sub_strings.size(); i++)
              {
                  if(case_insensitive_search(sub_strings[i], keywords_root))
                  {
                      return true;
                  }
              }
              return false;
          }
          
          //check for space
          else if(tokenize(query, " ").size() != 1)
          {
              vector<string> sub_strings = tokenize(query, " ");
              if(case_insensitive_search(query,keywords_root))
              {
                  return true;
              }
              else
              {
                  for(int i = 0; i<sub_strings.size(); i++)
                  {
                      if(case_insensitive_search(sub_strings[i], keywords_root))
                      {
                          return true;
                      }
                  }
                  return false;
              }
          }
          
          //single word search
          else
          {
              return case_insensitive_search(query, keywords_root);
          }
         
      }
      
      
      return false;
      
      
      
  }
  
  
};






vector <Website> create_objects()
{
    vector <Website> websites;

    fstream f;
    f.open("keywords.csv");
    string line;

    int counter = 0;

    if(f.is_open())
    {
        getline(f, line);
        while(f)
        {
            
            vector<string> keys = tokenize(line, ","); //seperating the fields
            Website website; //creating an object
            
            //set the url
            website.set_url(keys[0]);

            //set the website ID
            website.set_website_ID(counter);
            counter++;

            //set the file name
            vector<string> fname = tokenize(keys[0], ".");
            string tempname = fname[1] + ".txt";
            website.set_file_name(tempname);


            //set the number of keywords
            website.set_num_of_keywords(keys.size() - 1);

            //set the keyword root
            Node *root = NULL;  
            for(int i = 1; i < keys.size(); i++)
            {
                root = insert(root, keys[i]);
            }
            website.set_keywords(root);


            
            

            //adding the created instance to vector of other instances
            websites.push_back(website);
            getline(f,line);
        }

        f.close();
    }
    

    return websites;
}


class Webgraph
{
    public:
    int V;
    vector<Website> *adjlists;
    bool *visited;


    Webgraph(int V){
        this->V = V;
        adjlists = new vector<Website>[V];
        visited = new bool[V];
    }

    void addEdge(Website x, Website y){
        adjlists[x.get_website_ID()].push_back(y);
    }

    vector<Website> DFS(Website w, string query, vector<Website> &ws); 
    
};

Webgraph create_webgraph()
{ 



    vector<Website> ws = create_objects();

    Webgraph g(ws.size());

    map<string, Website> mp;

    for(auto itr = ws.begin(); itr != ws.end(); ++itr)
    {
        mp.insert(pair<string,Website>((*itr).url, *itr));
    }

    fstream f;
    f.open("webgraph.csv");
    string line;

    

    if(f.is_open())
    {
        getline(f, line);
        while(f){
            vector<string> src_dest = tokenize(line , ",");
            g.addEdge(mp[src_dest[0]],mp[src_dest[1]]);
            getline(f,line);
        }

        f.close();
    }

        return g;
}

vector<Website> Webgraph::DFS(Website w, string query, vector<Website> &matches)
{
    // Mark the current node as visited and
    
    visited[w.get_website_ID()] = true;
    vector<Website> adjlist = adjlists[w.get_website_ID()];
    matches.push_back(w);
    


    
 
    // Recur for all the vertices adjacent
    // to this vertex
    
    for (auto i = adjlist.begin(); i != adjlist.end(); ++i)
    {
        if ((!visited[(*i).get_website_ID()]) && ((*i).search_keywords(query)))
        {

            DFS(*i, query,matches);

        }
    }



    return matches;
}

vector<Website> search_web(string query, Webgraph g, vector<Website> websites)
{
    
    
    vector<Website> matches;
    
    
    int i = 0;
    
    //iterate through websites linearly until 1st match is found
    while((!websites[i].search_keywords(query)) && (i < websites.size()))
    {
        i++;
    }
    
    if(i == websites.size()) //no matches found
    {
        return matches;
    }
    
    else
    {
        //iterate through external_links of the website
        matches = g.DFS(websites[i], query, matches); //8alat
        
        return matches;
    }
}

vector <Website> sort_search_results(vector <Website> matches)
{
    return matches;
}

void display_website(Webgraph g, vector<Website> websites, vector<Website> matches, int choice);
void display_search_results(Webgraph g, vector<Website> websites, vector<Website> matches);
void display_search_menu(Webgraph g, vector<Website> websites);

void display_website(Webgraph g, vector<Website> websites, vector<Website> matches, int choice)
{
    cout<<endl<<"You're now viewing\n"<<matches[choice - 1].get_url()<<".\n";
    cout<<"Would you like to \n1.\tBack to search results\n2.\tNew search\n3.\tExit\n";
    int choice_2;
    cin>>choice_2;
    while(choice_2 < 1  || choice_2 > 3)
    {
        cout<<"Invalide choice\ntry again: ";
        cin>>choice_2;
    }

    if(choice_2 == 1)
    {
        cout<<endl;
        display_search_results(g, websites, matches);
    }

    else if(choice_2 == 2)
    {
        cout<<endl;
        display_search_menu(g, websites);
    }

    else
    {
        exit(0);
    }
}


void display_search_results(Webgraph g, vector<Website> websites, vector<Website> matches)
{
    cout<<endl<<"Search results:\n";

    if(matches.size()==0)
    {
        cout<<"No results match your query\n";
    }
    else
    {
        
        for(int i = 0; i <matches.size(); i++)
        {
            cout<<i+1<<"- "<<matches[i].get_url()<<endl;
        }
    }

    cout<<"Would you like to\n1.\tchoose a webpage to open\n2.\tNew search\n3.\tExit\n";
    cout<<"\n\nType in your choice: ";
    int choice;
    cin>>choice;
    if(choice == 1)
    {
        cout<<"\nEnter the index of the website you want to visit: ";
        int website_index;
        cin>>website_index;
        while(website_index < 1  || website_index > matches.size())
        {
            cout<<"Invalide website index\ntry again: ";
            cin>>website_index;
        }

        cout<<endl;
        display_website(g, websites, matches, website_index);
    }

    else if(choice == 2)
    {
        cout<<endl;
        display_search_menu(g, websites);
    }

    else
    {
        exit(0);
    }
}


void display_search_menu(Webgraph g, vector<Website> websites)
{
    cout<<"\nPlease enter your search query: \n";
    string query;
    getline(cin, query, '\n');
    vector<Website> matches = search_web(query, g, websites);
    cout<<endl<<"Search results:\n";

    if(matches.size()==0)
    {
        cout<<"No results match your query\n";
        display_search_menu(g, websites);
    }
    else
    {
        
        for(int i = 0; i <matches.size(); i++)
        {
            cout<<i+1<<"- "<<matches[i].get_url()<<endl;
        }
    }

    cout<<"Would you like to\n1.\tchoose a webpage to open\n2.\tNew search\n3.\tExit\n";
    cout<<"\n\nType in your choice: ";
    int choice;
    cin>>choice;
    while(choice < 1  || choice > 3)
    {
        cout<<"Invalide choice\ntry again: ";
        cin>>choice;
    }

    if(choice == 1)
    {
        cout<<"\nEnter the index of the website you want to visit: ";
        int website_index;
        cin>>website_index;
        while(website_index < 1  || website_index > matches.size())
        {
            cout<<"Invalide website index\ntry again: ";
            cin>>website_index;
        }


        
        cout<<endl;
        display_website(g, websites, matches, website_index);

    }

    else if(choice == 2)
    {
        cout<<endl;
        display_search_menu(g, websites);
    }

    else
    {
        exit(0);
    }
    


}


void display_welcome_menu()
{
    vector<Website> ws = create_objects();
    Webgraph g(ws.size());
    g = create_webgraph();

    cout<<"Welcome!\nWhat would you like to do?\n1.\tNew search\n2.\tExit\n\nType in your choice: ";
    int choice;
    cin>>choice;
    while(choice != 1 && choice != 2)
    {
        cout<<"Invalide choice\ntry again: ";
        cin>>choice;
    }

    if(choice == 1)
    {
        cout<<endl;
        display_search_menu(g, ws);
    }

    else{
        exit(0);
    }

}





int main()
{

    //display_welcome_menu();
     // vector<Website> ws = create_objects();
     // Webgraph g(ws.size());
     // g = create_webgraph();

    
   

    // vector<Website> m = search_web("auc", g, ws);
    // if(m.size()==0)
    // {
    //     cout<<"No results match your query\n";
    // }
    // else
    // {
    //  cout<<"Here are your search results!\n";
    //     for(int i = 0; i <m.size(); i++)
    //     {
    //         cout<<i+1<<"- "<<m[i].get_url()<<endl;
    //     }
    // }

    return 0;
}

