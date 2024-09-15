#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<sstream>
#include<limits>
using namespace std;

class Parking{
    private:
        string rno;
        string color;
        int slot;
        static int n;
    public:
        friend class InputMode;
        Parking(){
            rno="";
            color="";
            slot=0;
        }
        Parking(const string,const string);
        static void creation();
        string getrno(){
            return rno;
        }
        void parked(int);
        void unpark();
        void find();
};

int Parking::n=100;

Parking::Parking(const string rno,const string color){
    this->rno=rno;
    this->color=color;
}

void Parking::creation(){
    cout<<"Parking Lot created for "<<n<<" slots"<<endl;
    
}

void Parking::parked(int j){
    slot=j+1;
    cout<<"------------------------------------------------------"<<endl;
    cout<<"Car "<<rno<<" of "<<color<<" color parked at slot no. "<<slot<<endl;
    cout<<"------------------------------------------------------"<<endl;
                
}

void Parking::unpark(){
    cout<<"Unparked "<<rno<<" "<<color<<" from slot "<<slot<<endl;
    rno="";
    color="";
    slot=0;
}

void Parking::find(){
    cout<<rno<<" "<<color<<" parked at slot no. "<<slot<<endl;
}

class InputMode{

    Parking cars[100];
    bool avail[100]{false};
    public:
        void create(){
            Parking::creation();
        }

        void park(string rno,string color){
            int j=0;
            while(avail[j] && j<Parking::n){
                j++;
            }
            
            if(j<Parking::n){
                avail[j]=true;
                cars[j]=Parking(rno,color);
                cars[j].parked(j);
            }
            else    cout<<"Parking full"<<endl;
        }

        void unpark(string i){
            int k=0;
            for(auto c:cars){
                if(c.rno==i.substr(7)){
                    avail[k]=false;
                    c.unpark();
                    break;
                }
                k++;
            }
        }

        void find_slot(string i){
            int flag=0;
            for(auto c:cars){
                if(c.slot==stoi(i.substr(18))){
                    flag=1;
                    c.find();
                    break;
                }
                
            }
            if(!flag){
                cout<<"Car not Parked here!!"<<endl;
            }
        }

        void find_number(string i){
            int flag=0;
            for(auto c:cars){
                if(c.rno==i.substr(16)){
                    flag=1;
                    c.find();
                    break;
                }
                
            }
            if(!flag){
                cout<<"Car not Parked here!!"<<endl;
            }
        }
        
        void find_color(string i){
            int flag=0;
            for(auto c:cars){
                if(c.color==i.substr(9)){
                    flag=1;
                    c.find();
                }
                
            }
            if(!flag){
                cout<<"Car not Parked here!!"<<endl;
            }
        }

        void readCommands(string input){
            istringstream iss(input);
            string command,rno,color;
            iss>>command;
            if(command=="create_parking_lot"){
                create();
            }
            else if(command=="park"){
                iss>>rno>>color;
                park(rno,color);
                
            }
            else if (input.substr(0,6)=="unpark"){
                unpark(input);
            }
            else if(input.substr(0,17)=="find_parking_slot"){
                find_slot(input);
            }
            else if(input.substr(0,15)=="find_car_number"){
                find_number(input);
            }
            else if(input.substr(0,8)=="find_car"){
                find_color(input);
                }
            else{
                cout<<""<<endl;
            }
        }
        void keyboard(){
        
            while(1){
                cout<<endl;
                string input;
                cout<<"Command(to exit : 1): ";
                getline(cin,input);
                
                if(!(input=="1")){
                    readCommands(input);
                }
                else {
                    break;
                }
            }
        }

        void file(const string& filename){
            ifstream inputFile(filename);
            if (!inputFile) { 
                cerr << "Error opening file!" << endl;
                return;
            }
            string line;
            while (getline(inputFile, line)) { 
                cout<<endl;
                cout<<"Command: "<<line<<endl;
                readCommands(line);
            }

            inputFile.close();
        }
};

int main(){

    int mode;
    cout<<"Select input mode (1 for keyboard, 2 for file): ";
    cin>>mode;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer
    InputMode im;
    if(mode==1){
        im.keyboard();
    }
    else if(mode==2){
        string filename;
        cout<<"Enter file name: ";
        getline(cin,filename);
        im.file(filename);
    }
    
    return 0;
}
