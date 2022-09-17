#include<bits/stdc++.h>
#include<fstream>

using namespace std;


/**
* @author Sagar_214101044
* @author Shubham_214101053
*/

/*
*set to store distinct file-----
*/
set<string> file_list;

/*
*class of i-node
*/
class i_node
{
    // file name
    string file__name;
    //vector of file block
    vector<int> file_block;
    public:
    	
        // vector of i-node in which all file i-node is stored
        vector<i_node> vec_of_inode;  

        /*
        *Search function-----------
        */
        void search(string file_name)
        {
            //check file is present or not!!!
            if(file_list.find(file_name) == file_list.end())
            {
                cout<<"File  does not exit"<<endl;
                return;
            }

            //find file---
            for(auto it : vec_of_inode)
            {
                
                if(it.file__name == file_name)
                {
                    //iterate in each block and read data...
                    for(auto itr : it.file_block)
                    {
                        string str = to_string(itr);
                        str = str+".txt";

                        ifstream file_read;
                        file_read.open(str);

                        string line;
                        getline(file_read,line);

                        cout<<line;
                    }
                }
            }
            cout<<endl;
        }

        /*
        *Create function-----------
        */
        void create_file(string file_name,string content)
        {
        	//first check this name file is not exist!!!!!!!!!
            if(file_list.find(file_name) != file_list.end())
            {
                cout<<"File already exist!!!!!!!!!!!!!!"<<endl;
                return;
            }
            //if not exist that file then create .......
            int start = 0;
            i_node obj;
            obj.file__name =  file_name;
            file_list.insert(file_name);
            srand(time(0));

            while(start < content.length())
            {
                string s = content.substr(start,4);
                start += 4;
                int block_no = rand();
                obj.file_block.push_back(block_no);

                string block_name = to_string(block_no)+".txt";
                ofstream File(block_name);
                File<<s;

                File.close();
            }
            vec_of_inode.push_back(obj);
            cout<<"File created successfully!!!"<<endl;
        }

        /*
        *Delete function-----------
        */
        void delete_file(string file_name)
        {
        	//first check this name file is exist!!!!!!!!!
            if(file_list.find(file_name) == file_list.end())
            {
                cout<<"File not exit!!!!!!!!!"<<endl;
                return;
            }
            //if exist then delete it......
            int i = 0;
            for(auto it : vec_of_inode )
            {
                if(it.file__name == file_name)
                {
                      for(auto itr : it.file_block )
                      {
                          string str_n = to_string(itr);
                          str_n = str_n + ".txt";
                          char * str = new char [str_n.length()+1];
                          strcpy(str,str_n.c_str());
                          int tt__ = remove(str);
                      }
                      vec_of_inode.erase(vec_of_inode.begin()+i);
                      break;
                }
                i++;
            }
            auto it = file_list.find(file_name);
            file_list.erase(it);
            cout<<"File Deleted Successfully!!!!"<<endl;
        }

        /*
        *Rename function-----------
        */
        void rename_file(string file_1 , string file_2)
        {
            auto itr = file_list.find(file_1);
            if(itr == file_list.end())
            {
                cout<<"File not exit!!!!!!!!!"<<endl;
                return;
            }

            for(int i = 0 ; i < vec_of_inode.size() ; i++)
            {
                if(vec_of_inode[i].file__name == file_1)
                {
                    vec_of_inode[i].file__name = file_2;
                    break;
                }
            }

            file_list.erase(itr);
            file_list.insert(file_2);
            cout<<file_1<<" Renamed to "<<file_2<<endl;
        }

        /*
        *List function-----------
        */
        void list_()
        {
            for(auto itr : file_list)
             {
                 int i = 0;
                 for(auto it : vec_of_inode)
                 {
                     if(itr == it.file__name)
                     {
                        cout<<itr<<"   "<<i<<endl;
                        break;
                     }
                     i++;
                 }
             }
        }
};



int main()
{
    
    string file_name;
    string content;

	//create i-node object....
    i_node obj_;
    bool flag = true;
    while(flag)
    {
    	//command to take command from users....

        string command;
        string cmnd = "S:\\CS_Lab\\Assignment_2\\Ques_2>";
        cout<<cmnd;
        getline(cin,command);
        string cmd = command.substr(0,2);
        
        //if cmd is mf then we have to create file....
	//  mf File1 “This is file 1”
        if(cmd == "mf")
        {
            file_name = "";
            int i;
            for(i = 3 ; i < command.length() ; i++)
            {
                if(command[i]==' ')
                    break;
                file_name += command[i];
            }
            content = command.substr(i+2);
            content.resize(content.size()-1);

            obj_.create_file(file_name , content);
        }

		//if cmd is pf then we have to read the file.....
		//pf file-name 
        else if(cmd == "pf")
        {
            file_name = command.substr(3);
            obj_.search(file_name);
        }

		//if cmd is rf then we have to rename the file ....
		// rf file-name1 file-name2
        else if(cmd == "rf")
        {
            string file_1 = "";
            int i ;
            for(i = 3 ; i < command.length() ; i++)
            {
                if(command[i]==' ')
                    break;
                file_1 += command[i];
            }
            string file_2 = command.substr(i+1);
            obj_.rename_file(file_1 , file_2);
        }

		//if cmd is ls then we have to print all file in list.....
		// ls
        else if(cmd == "ls")
        {
             obj_.list_();
        }

		//if cmd is df then we have to delete file...
		//df File1
        else if(cmd == "df")
        {
            string dfile_name = command.substr(3);
            obj_.delete_file(dfile_name);
        }

		//if cmd if ex then we have to exit the program......
        else if(cmd == "ex")
        {
            flag = false;
        }

        else
        {
            cout<<"Write a correct command"<<endl;
        }

    }
    return 0;
}
