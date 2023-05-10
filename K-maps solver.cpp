#include <bits/stdc++.h>
using namespace std;


bool is_duplicated(vector<int> v)
{
    vector<int> a = v;
    sort(a.begin(), a.end());
    const bool hasDuplicates = std::adjacent_find(a.begin(), a.end()) != a.end();
    return hasDuplicates;
}


bool is_file_exist(string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}


int get_testcases_no(string p)
{
    fstream input_file;
    input_file.open(p, ios::in);
    if (input_file.is_open())
	{
	    string line;
	    getline(input_file, line);
	    input_file.close();
	    
	    return int(line[0]) - 48; // convert ascii value to decimal
	}
	else return 0;
}

int get_no_of_lines(string p)
{
    fstream input_file;
    input_file.open(p, ios::in);
    if (input_file.is_open())
	{
	    string line;
	    int count = -1;
	    while(getline(input_file, line))
	    {
	        
	        if((int(line[0]) - 48) != 2 and (int(line[0]) - 48) != 3 and count >=0)
	        {
	            cout<<"This program only supports 2 and 3-variabled K-maps\n";
	            exit(-1);
	        }
	        count++;
	    }
	    
	    input_file.close();
	    return count;
	}
	else return 0;
    
}



void check_no_of_minterms(string p)
{
    fstream input_file;
    input_file.open(p, ios::in);
    if (input_file.is_open())
	{
	    string line;
	    int count = -1;
	    while(getline(input_file, line))
	    {
	        if(count == -1)
	        {
	            count++;
	            continue;
	        }
	        
	        if((int(line[2]) - 48) > pow(2,(int(line[0]) - 48)))
	        {
	            cout<<"number of minterms greater than what the number of variables can accomodate\n";
	            exit(-1);
	        }

	        count++;
	    }
	}
	input_file.close();
}


void check_minterms_existence(string p)
{
    fstream input_file;
    input_file.open(p, ios::in);
    if (input_file.is_open())
	{
	    string line;
	    int count = -1;
	    while(getline(input_file, line))
	    {
	        if((count == -1) and line.length() != 2)
	        {
	            cout<<"incorrect format: characters entered beside number of test cases\n";
	            input_file.close();
	            exit(-1);
	        }
	        else if((count == -1) and line.length() == 2)
	        {
	            count++;
	            continue;
	        }
	        else if(line.length() != 2 * (int(line[2]) - 48) + 4)
	        {
	            cout<<"incorrect format: minterms are not formatted properly\nenter the correct number of minterms and separate them by spaces\n";
	            cout<<"make sure that the last line is empty\n";
	            input_file.close();
	            exit(-1);
	        }
	        
	        else
	        {
	            count++;
	            continue;
	        }
	        
	        
	        count++;
	    }
	}
	input_file.close();
	
}

void check_minterms_accuracy(string p)
{
    fstream input_file;
    input_file.open(p, ios::in);
    if (input_file.is_open())
	{
	    string line;
	    int count = -1;
	    while(getline(input_file, line))
	    {
	        if(count == -1)
	        {
	            count++;
	            continue;
	        }
	        
	        if((int(line[2]) - 48) == 0)
	        {
	            count++;
	            continue;
	        }
	        
	        else if((int(line[0]) - 48) == 3)
	        {
	            vector<int> minterms;
	            
	            for(int i = 4; i<line.length(); i+=2)
	            {
	                minterms.push_back(int(line[i]));
	                if((int(line[i]) > 55) or (int(line[i]) < 48))
	                {
	                    cout<<"out of range\n";
	                    exit(-1);
	                }
	            }
	            if(is_duplicated(minterms))
	            {
	                cout<<"can't have duplicate entries\n";
	                exit(-1);
	            }
	        }
	        
	        else if((int(line[0]) - 48) == 2)
	        {
	            vector<int> minterms;
	            
	            for(int i = 4; i<line.length(); i+=2)
	            {
	                minterms.push_back(int(line[i]));
	                if((int(line[i]) > 51) or (int(line[i]) < 48))
	                {
	                    cout<<"out of range\n";
	                    exit(-1);
	                }
	            }
	            if(is_duplicated(minterms))
	            {
	                cout<<"can't have duplicate entries\n";
	                exit(-1);
	            }
	        }
	    }
	}
	input_file.close();
}


vector<vector<vector<bool>>> construct_two_variable_kmaps(string p)
{   
    vector<vector<vector<bool>>> two_variable_kmaps;
    fstream input_file;
    input_file.open(p, ios::in);
    if (input_file.is_open())
	{
	    string line;
	    int count = -1;
	    while(getline(input_file, line))
	    {
	        if(count == -1)
	        {
	            count++;
	            continue;
	        }
	        
	        if((int(line[0]) - 48) == 3)
	        {
    	       count++;
    	       continue;
	        }
	        
	        if((int(line[0]) - 48) == 2)
	        {
	            cout<<count + 1<<"-\nKmap:";
	            vector<vector<bool>> kmap;
	            kmap.resize(2);
                for (int i = 0; i < 2; ++i)
                {
                    kmap[i].resize(2);
                }
    	        for(int i=0; i<2; i++)
    	        {
    	            for(int j =0; j<2; j++)
    	            {
    	                kmap[i][j] = 0; //initializing the kmap with zeroes
    	            }
    	        }
    	        vector<int> minterms;
    	        for(int i = 4; i<line.length(); i+=2)
                {
                    minterms.push_back(int(line[i]) - 48);
                }
                // for (auto i: minterms)
                // {
                //     cout << i << ' ';
                // }
                if (find(minterms.begin(), minterms.end(), 0) != minterms.end())
                {
                    kmap[0][0] = 1;
                }
                if (find(minterms.begin(), minterms.end(), 1) != minterms.end())
                {
                    kmap[1][0] = 1;
                }
                if (find(minterms.begin(), minterms.end(), 2) != minterms.end())
                {
                    kmap[0][1] = 1;
                }
                if (find(minterms.begin(), minterms.end(), 3) != minterms.end())
                {
                    kmap[1][1] = 1;
                }
                
                cout<<endl<<endl;
                for(int i=0; i<2; i++)
    	        {
    	            for(int j =0; j<2; j++)
    	            {
    	                cout<<kmap[i][j]<<"  ";
    	            }
    	            cout<<endl;
    	        }
    	        cout<<endl<<endl<<endl;
    	        
    	        two_variable_kmaps.push_back(kmap);
                
	        }
	        
	        count++;
	    }
	}
	input_file.close();
	return two_variable_kmaps;
}



vector<vector<vector<bool>>> construct_three_variable_kmaps(string p)
{   
    vector<vector<vector<bool>>> three_variable_kmaps;
    fstream input_file;
    input_file.open(p, ios::in);
    if (input_file.is_open())
	{
	    string line;
	    int count = -1;
	    while(getline(input_file, line))
	    {
	        if(count == -1)
	        {
	            count++;
	            continue;
	        }
	        
	        if((int(line[0]) - 48) == 3)
	        {
	            cout<<count + 1<<"-\nKmap:";
    	        vector<vector<bool>> kmap;
	            kmap.resize(2);
                for (int i = 0; i < 2; ++i)
                {
                    kmap[i].resize(4);
                }
    	        for(int i=0; i<2; i++)
    	        {
    	            for(int j =0; j<4; j++)
    	            {
    	                kmap[i][j] = 0; //initializing the kmap with zeroes
    	            }
    	        }
    	        vector<int> minterms;
    	        for(int i = 4; i<line.length(); i+=2)
                {
                    minterms.push_back(int(line[i]) - 48);
                }
                // for (auto i: minterms)
                // {
                //     cout << i << ' ';
                // }
                if (find(minterms.begin(), minterms.end(), 0) != minterms.end())
                {
                    kmap[0][0] = 1;
                }
                if (find(minterms.begin(), minterms.end(), 1) != minterms.end())
                {
                    kmap[1][0] = 1;
                }
                if (find(minterms.begin(), minterms.end(), 2) != minterms.end())
                {
                    kmap[0][1] = 1;
                }
                if (find(minterms.begin(), minterms.end(), 3) != minterms.end())
                {
                    kmap[1][1] = 1;
                }
                if (find(minterms.begin(), minterms.end(), 4) != minterms.end())
                {
                    kmap[0][3] = 1;
                }
                if (find(minterms.begin(), minterms.end(), 5) != minterms.end())
                {
                    kmap[1][3] = 1;
                }
                if (find(minterms.begin(), minterms.end(), 6) != minterms.end())
                {
                    kmap[0][2] = 1;
                }
                if (find(minterms.begin(), minterms.end(), 7) != minterms.end())
                {
                    kmap[1][2] = 1;
                }
                
                cout<<endl<<endl;
                for(int i=0; i<2; i++)
    	        {
    	            for(int j =0; j<4; j++)
    	            {
    	                cout<<kmap[i][j]<<"  ";
    	            }
    	            cout<<endl;
    	        }
    	        cout<<endl<<endl<<endl;
    	        
    	        three_variable_kmaps.push_back(kmap);
                
	        }
	        
	        if((int(line[0]) - 48) == 2)
	        {
	           count++;
	           continue;
	        }
	        
	        count++;
	    }
	}
	input_file.close();
	return three_variable_kmaps;
}


bool is_adjacent(string a, string b)   //to check if 2 binary numbers are adjacent
{
    int counter = 0;
    for(int i=0; i<a.length(); i++)
    {
        if(a[i] != b[i])
        {
            counter++;
        }
    }
    
    if(counter == 1)
    {
        return true;
    }
    else return false;
    
}


string invert_bit(string s, int position)
{
    if(s[position] == '1')
    {
        s[position] = '0';
    }
    
    else if(s[position] == '0')
    {
        s[position] = '1';
    }
    
    return s;
}


vector<vector<vector<string>>> get_two_variabled_implicants(vector<vector<vector<bool>>> two_kmaps)
{
    vector<vector<vector<string>>> implicants;
    
    
    for(vector<vector<vector<bool>>>::const_iterator i = two_kmaps.begin(); i != two_kmaps.end(); ++i)
    {
        vector<vector<string>> kmap_implicants;
        int counter = 0; //counts total number of ones in the kmap
        for(vector<vector<bool>>::const_iterator j = i->begin(); j != i->end(); ++j)
        {
            
            for(vector<bool>::const_iterator k = j->begin(); k != j->end(); ++k)
            { 

                if(*k == 1)
                {
                    counter++;
                    vector<string> osi;
                    vector<string> tsi1;
                    vector<string> tsi2;
                    string one_square_implicant = "";
                    one_square_implicant += to_string(distance(j->begin(), k));
                    one_square_implicant += to_string(distance(i->begin(), j));
                    osi.push_back(one_square_implicant);
                    kmap_implicants.push_back(osi);
                    string one_square_implicant_adj1 = invert_bit(one_square_implicant, 0);
                    if((*i)[int(one_square_implicant_adj1[1]) - 48][int(one_square_implicant_adj1[0]) - 48] == 1)
                    {
                        tsi1.push_back(one_square_implicant);
                        tsi1.push_back(one_square_implicant_adj1);
                        sort(tsi1.begin(), tsi1.end());
                        kmap_implicants.push_back(tsi1);
                    }
                    
                    string one_square_implicant_adj2 = invert_bit(one_square_implicant, 1);
                    if((*i)[int(one_square_implicant_adj2[1]) - 48][int(one_square_implicant_adj2[0]) - 48] == 1)
                    {
                        tsi2.push_back(one_square_implicant);
                        tsi2.push_back(one_square_implicant_adj2);
                        sort(tsi2.begin(), tsi2.end());
                        kmap_implicants.push_back(tsi2);
                    }
                    
                }
            }
        }
        //cout<<"counter = "<<counter<<endl;
        if(counter == 4)
        {
            vector<string> fsi;
            fsi.push_back("00");
            fsi.push_back("01");
            fsi.push_back("10");
            fsi.push_back("11");
            sort(fsi.begin(), fsi.end());
            kmap_implicants.push_back(fsi);
        }
        
        sort(kmap_implicants.begin(), kmap_implicants.end());
        kmap_implicants.erase( unique( kmap_implicants.begin(), kmap_implicants.end() ), kmap_implicants.end() ); //remove duplicte implicants
        
        implicants.push_back(kmap_implicants);
    }
    
    return implicants;
    
}

void get_three_variabled_implicants(vector<vector<vector<bool>>> three_kmaps)
{
    
}


vector<vector<vector<string>>> get_two_variabled_prime_implicants(vector<vector<vector<string>>> two_kmap_implicants) //eliminates small impicants that are subsets of big ones
{
     vector<vector<vector<string>>> prime_implicants;
     for( int i = 0; i< two_kmap_implicants.size(); i++)
     {
        vector<vector<string>> kmap_prime_implicants;
        for( int j = 0; j < two_kmap_implicants[i].size(); j++)
        {
            int counter =0;
            for( int k = 0; k < two_kmap_implicants[i].size(); k++) 
            { 
                if (includes(two_kmap_implicants[i][k].begin(), two_kmap_implicants[i][k].end(), two_kmap_implicants[i][j].begin(), two_kmap_implicants[i][j].end())) //error here
                {   
                    counter++; 
                }
            }
            if (counter == 1)
            {
                kmap_prime_implicants.push_back(two_kmap_implicants[i][j]);
            }
        }
        prime_implicants.push_back(kmap_prime_implicants);
     }
     return prime_implicants;
}


void get_three_variabled_prime_implicants(vector<vector<vector<bool>>> three_kmap_implicants)
{
    
}


void create_two_variable_bool_expressions(vector<vector<vector<string>>> two_variable_prime_implicants)
{
    
    
    vector<vector<vector<string>>> bool_expressions;
    bool_expressions.resize(two_variable_prime_implicants.size());
    for( int i = 0; i< two_variable_prime_implicants.size(); i++)
    {
        cout<<"here1000\n";
        if(two_variable_prime_implicants[i].empty()) //{0,0,0,0}
        {
            cout<<"here0\n";
            bool_expressions[i].resize(1);
            bool_expressions[i][0].resize(1);
            bool_expressions[i] = {{"0"}};
            cout<<"F = "<<bool_expressions[i][0][0]<<endl;
        }
        if(two_variable_prime_implicants[i].size() == 1 and two_variable_prime_implicants[i][0].size() == 4) //{1,1,1,1}
        {
            cout<<"here1\n";
            bool_expressions[i].resize(1);
            bool_expressions[i][0].resize(1);
            bool_expressions[i] = {{"1"}};
            cout<<"F = "<<bool_expressions[i][0][0]<<endl;
        }
        else
        {
            for(int j = 0; j < two_variable_prime_implicants[i].size(); j++)
            {
                for(int k = 0; k< two_variable_prime_implicants[i][j].size(); k++)
                {
                    if(two_variable_prime_implicants[i][j][k] == "00")
                    {
                        bool_expressions[i][j][k].push_back("A'B'");
                    }
                    
                    if(two_variable_prime_implicants[i][j][k] == "01")
                    {
                        bool_expressions[i][j][k].push_back("A'B");
                    }
                    
                    if(two_variable_prime_implicants[i][j][k] == "10")
                    {
                        bool_expressions[i][j][k].push_back("AB'");
                    }
                    
                    if(two_variable_prime_implicants[i][j][k] == "11")
                    {
                        bool_expressions[i][j][k].push_back("AB");
                    }
                }
            }
        }
    
    } 
    
}


int main()
{
	string PATH;
	cout<<"Please enter your file path\n";
	cin>>PATH;
	cout<<endl;
	
	while(!is_file_exist(PATH))
	{
	    cout<<"This file path does not exist on your machine. Try again.\n";
	    cin>>PATH;
	}


 	
    if(get_no_of_lines(PATH) != get_testcases_no(PATH))
    {
        cout<<"incorrect number of test cases\n";
        exit(-1);
    }
	   
	check_no_of_minterms(PATH);
	check_minterms_existence(PATH);
	check_minterms_accuracy(PATH);
	
	cout<<endl<<endl<<endl;
	
	vector<vector<vector<bool>>> three_v_kmaps;
	vector<vector<vector<bool>>> two_v_kmaps;
	
	two_v_kmaps = construct_two_variable_kmaps(PATH);
	three_v_kmaps = construct_three_variable_kmaps(PATH);
	
	cout<<endl<<endl<<endl;
	
	
   for( vector<vector<vector<bool>>>::const_iterator i = two_v_kmaps.begin(); i != two_v_kmaps.end(); ++i)
   {
       cout<<endl<<endl<<endl;
       for( vector<vector<bool>>::const_iterator j = i->begin(); j != i->end(); ++j)
       {
            cout<<endl;
            for( vector<bool>::const_iterator k = j->begin(); k != j->end(); ++k)
            { 
                     cout<<*k<<' ';
            }
       }
   }
   
   
   for( vector<vector<vector<bool>>>::const_iterator i = three_v_kmaps.begin(); i != three_v_kmaps.end(); ++i)
   {
       cout<<endl<<endl<<endl;
       for( vector<vector<bool>>::const_iterator j = i->begin(); j != i->end(); ++j)
       {
            cout<<endl;
            for( vector<bool>::const_iterator k = j->begin(); k != j->end(); ++k)
            { 
                     cout<<*k<<' ';
            }
       }
   }
   
   
   cout<<endl<<endl<<endl;
   
//   vector<vector<vector<string>>> v = 
   create_two_variable_bool_expressions(get_two_variabled_prime_implicants(get_two_variabled_implicants(construct_two_variable_kmaps(PATH))));
   
//   for( vector<vector<vector<string>>>::const_iterator i = v.begin(); i != v.end(); ++i)
//   {
//       cout<<endl;
//       for( vector<vector<string>>::const_iterator j = i->begin(); j != i->end(); ++j)
//       {
//             cout<<"\n{";
//             for( vector<string>::const_iterator k = j->begin(); k != j->end(); ++k)
//             { 
//                      cout<<*k<<',';
//             }
//             cout<<"}";
//       }
//   }
   
   
	
	return 0;
}