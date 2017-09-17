#include <Client_DSSE.h>
#include "Server_DSSE.h"
#include <DSSE_Param.h>
#include <fstream>



using namespace std;

void printMenu();

bool fexists(string filename_with_path)
{
  ifstream ifile(filename_with_path.c_str());
  if(!ifile.is_open())
      return false;
  return true;
}

int main(int argc, char **argv)
{
    #if defined(LOAD_FROM_DISK)
        cout<<"MODE: LOAD DISK"<<endl;
    #else
        cout<<"MODE: MEMORY"<<endl;
    #endif
    cout<<"# FILE:"<<MAX_NUM_OF_FILES<<endl;
    cout<<"# KW: "<<MAX_NUM_KEYWORDS<<endl;

    cout<<"server ID:"<<PEER_ADDRESS<<endl;



    
    
    auto start = time_now;
    auto end = time_now;
	
    setbuf(stdout,NULL);
    
    

    int choice;
    cout << "CLIENT(1) or SERVER(2): ";
	cin >> choice;
	cout << endl;
	
    do
    {
        if(choice == 2)
        {
            Server_DSSE* server_dsse = new Server_DSSE();
            server_dsse->start();
            
            return 0;
        }
        else
        {
            Client_DSSE*  client_dsse = new Client_DSSE();
    
            string str_keyword;        
            std::string update_loc = gcsUpdateFilepath;
            string updating_filename;
            
            TYPE_COUNTER search_result;
            while (1)
            {
                int selection =-1;
                do
                {
                    printMenu();
                    cout<<"Select your choice: ";
                    while(!(cin>>selection))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cout<<"Invalid input. Try again: ";
                    }
                    
                }while(selection < 0 && selection >4);
                switch(selection)
                {
                case 0:
                    client_dsse->genMaster_key();
                    break;
                case 1:
                    //start = time_now;
                    client_dsse->createEncrypted_data_structure();
                    //end = time_now;
                    //cout<<"Elapsed time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()<<" ms"<<endl;
                    break;
                case 2:
                    str_keyword = "the";
                    //cout<<"Keyword search: ";
                    //cin>>str_keyword;
                    //std::transform(str_keyword.begin(),str_keyword.end(),str_keyword.begin(),::tolower);
                    
                    client_dsse->searchKeyword(str_keyword,search_result);

        //            reset(ROW);
                    
                    cout<<" Keyword *"<<str_keyword<<"* appeared in "<<search_result <<" files"<<endl;
                    
                    break;
                case 3:
        /*
                    cout<<"Specify the filename want to add: ";
                    cin>>updating_filename;
                    if(!fexists(gcsUpdateFilepath+updating_filename))
                    {
                        cout<<endl<<"File not found! Please put/check the file into/in update folder"<<endl;
                        break;
                    }
                     */
                    
                    updating_filename = "add";
                    client_dsse->addFile(updating_filename,gcsUpdateFilepath);
                    
                    cout<<"Done!"<<endl;
                    
                    break;
                case 4:
                //    cout<<"Specify the filename want to delete: ";
                //    cin>>updating_filename;
                  
                    updating_filename = "add";
                    //start = time_now;
                    client_dsse->delFile(updating_filename,gcsUpdateFilepath);
                    //end = time_now;
                    //cout<<"Total Elapsed time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()<<" ms"<<endl;
                    
                    break;
                
                default:
                    break;
                }
            }
        }
    }while(choice!=1 && choice !=2); 
    
    
    

    
    
    
    
    
    
    
    return 0;
    
}
void printMenu()
{
    cout<<"---------------"<<endl<<endl;
    cout<<"0. (Re)generate keys"<<endl;
    cout<<"1. (Re)build data structure"<<endl;
    cout<<"2. Keyword search: "<<endl;
    cout<<"3. Add files"<<endl;
    cout<<"4. Delete files"<<endl<<endl;;
    cout<<"---------------"<<endl;
}
