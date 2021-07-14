#include<iostream>
#include<vector>
#include<cstring>
#include<string>
#include<bits/stdc++.h>
using namespace std;

int ctoi(char a)
{
    int temp = a;
    return temp - 48;
}
class state
{
public:
    int number;
    string label;
    vector<state*>List_to_other_states;
    state(){}
    state(int number)
    {
        this->number = number;
    }
    int GetNumber()
    {
        return this->number;
    }
    vector<int> GetAllNumber()
    {
        vector<int>temp;
        for(int i = 0 ; i<List_to_other_states.size();i++)
        {
            int x = List_to_other_states[i]->GetNumber();
            temp.push_back(x);
        }
        return temp;
    }
    void SetUp(string somestring)
    {
        int SIZE = somestring.length();
        int i =0;
        while(i<SIZE)
        {
            label = label+ somestring.at(i);
            i=i+2;
        }

    }
    void PrintOut()
    {
        cout<<label;
    }
    string GetLabel()
    {
        return this->label;
    }
    void SetTransition(state* Other)
    {
        List_to_other_states.push_back(Other);
    }
    vector<state*> GetListOfStates()
    {
        return this->List_to_other_states;
    }
    bool CheckTransition(int some_number)
    {
        for( int i = 0 ; i < List_to_other_states.size();i++)
        {
            if(List_to_other_states[i]->GetNumber()==some_number)
                return true;
        }
        return false;
    }

};

vector<state> Initialize()
{
    int num_of_states;
    cout<<"How many states: ";
    cin>>num_of_states;
    vector<state>List_of_State;
    for( int i = 0 ; i< num_of_states;i++)
    {
        state temp_state(i);;
        printf("label of state s%d: ",i);
        string temp;
        cin>>temp;
        temp_state.SetUp(temp);
        List_of_State.push_back(temp_state);
    }
    return List_of_State;
}
void Print(vector<state>List_of_States)
{
    for( int i = 0 ; i<List_of_States.size();i++)
    {
        cout<<"s"<<i<<": ";
        List_of_States[i].PrintOut();
        cout<<endl;
    }
}
void PrintOut_LinkedNode(state* State)
    {
        if(State == NULL)
        {
            return;
        }
        vector<state*>temp = State->GetListOfStates();
        State->PrintOut();
        if(temp.size()==0)
            {

                return;
            }
        else
        {
            for(int  i = 0; i <temp.size();i++)
            {
                PrintOut_LinkedNode(temp[i]);
            }
        }
    }



vector<state> Set_transition(vector<state>List_of_States)
{
    cout<<"Set transition (press e to stop) : ";
    string input;
    cin>>input;
    if(input.at(0)=='0')
    {
        while(true)
        {
            if(input.at(0)=='e')
            {
                cout<<"The end of Transition Setup! "<<endl;
                return List_of_States;
            }
            else
            {
                char char1 = input.at(0);
                char char2 = input.at(2);
                int i_temp1 = ctoi(char1);
                int i_temp2 = ctoi(char2);
                List_of_States[i_temp1].SetTransition(&List_of_States[i_temp2]);
                cout<<"Set transition (press e to stop) : ";
                cin>>input;
            }
        }
    }
    else
    {
        cout<<"The first transition need the initial of '0'. Please rerun this program and type correctly";
        return List_of_States;
    }



}

string PathSetUp() //return the path with out -
{
    string String_Path;
    cout<<"Enter a path: ";
    cin>>String_Path;
    int SIZE = String_Path.length();
    string New_String_Path;
    for(int i = 0 ; i<SIZE;i=i+2)
    {
        New_String_Path+=String_Path.at(i);
    }

    return New_String_Path;
}
bool FormulaCheck(string OriginalPath, string theta, vector<state>List_of_state, string Pattern)
{
   if(theta.length()==2)
   {
       if(theta.at(0)=='F')
       {
           for(int i = 0;i<Pattern.length();i++)
           {
               string label;
               int index = ctoi(Pattern.at(i));
               label = List_of_state[index].GetLabel();
               for(int j = 0;j<label.length();j++)
               {
                   if (theta.at(1)==label.at(j))
                    return true;
               }
           }
           return false;
       }
       if(theta.at(0)=='G')
       {
           int result=0;
           for(int i=0;i<OriginalPath.length();i++)
           {
               string label;
               int index = ctoi(OriginalPath.at(i));
               label = List_of_state[index].GetLabel();
               for(int j =0;j<label.length();j++)
               {
                   if(theta.at(1)==label.at(j))
                    result++;
               }
           }
           //Finishing the loop but result still be 1, means that it passed the Global test;
           if(result>=OriginalPath.length())
                return true;
            else
                return false;

       }
       if(theta.at(0)=='X')
       {
           string label;
           int index = ctoi(OriginalPath.at(1));
           label = List_of_state[index].GetLabel();
           for(int j = 0;j<label.length();j++)
           {
               if(label.at(j)==theta.at(1))
               {
                   return true;
               }
           }
           return false;
       }

   }
   if(theta.length()==3)
   {
       char label1 = theta.at(0);
       char label2 = theta.at(2);
       bool temp_result;
       bool if_theta2_exists;
       string label_list;
       for(int i = 0 ; i<OriginalPath.length();i++)
       {
           int index = ctoi(OriginalPath.at(i));
           label_list= List_of_state[index].GetLabel();
           for( int j=0;j<label_list.length();j++)
           {
               if(label2 == label_list.at(j))
                {
                    if_theta2_exists++;
                    return true;
                }
               else
               {
                   if(label1==label_list.at(j))
                   {
                       temp_result++;
                   }
               }
           }
           if(temp_result==0)
            return false;
       }
       if(if_theta2_exists==0)
        return false;

   }
}
bool CheckPath(string New_String_Path,vector<state>List_of_States)
{
    //023013
    for(int i =  0 ; i <New_String_Path.size()-1;i++ )
    {
        char char1 = New_String_Path.at(i);
        char char2 = New_String_Path.at(i+1);
        int numb1 = ctoi(char1);
        int numb2 = ctoi(char2);
        //cout<<numb1<<" "<<numb2<<endl;
        if(List_of_States[numb1].CheckTransition(numb2)==0)
            return false;
    }
        return true;
}

string GetPattern(string New_String_Path)
{
    int PATH_SIZE = New_String_Path.length();
    string result;
    result +=New_String_Path.at(PATH_SIZE-1);
    for( int i = PATH_SIZE-2;i>=0;i--)
    {
        if(result.at(0)==New_String_Path.at(i))
            {
                reverse(result.begin(),result.end());
                return result;
            }
        else
            result += New_String_Path.at(i);
    }


}







void Determine(vector<state>List_of_states)
{
    string New_string_path = PathSetUp();
    string input_LTL;
    cout<<"Enter the LTL formula: ";
    cin>>input_LTL;
    if(CheckPath(New_string_path,List_of_states))
        {
            string Final_Pattern = GetPattern(New_string_path);
            if(FormulaCheck(New_string_path,input_LTL,List_of_states,Final_Pattern)==1)
            {
                cout<<"Yes";
                return;
            }
            else
            {
                cout<<"No";
                return;
            }

        }
    else
        {
            cout<<"No path";
            return;
        }
}

int main()
{
    vector<state>List_of_States = Initialize();


    List_of_States = Set_transition(List_of_States);


    Determine(List_of_States);

}
