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
bool contains(string a_string, char a_char)
{
    bool result=false;
    for(int i = 0 ; i< a_string.length();i++)
    {
        if(a_string.at(i)==a_char)
        {
            result = true;
            break;
        }

    }
    return result;
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
void Print_Path(vector<string>path)
{
    cout<<"Here are all current paths: "<<endl;
    for(int i =0;i<path.size();i++)
        cout<<path[i]<<",";
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

vector<string> Path_Generator(vector<state>List_of_states, int initial_state,vector<string>result)
{
    string string_convert = to_string(initial_state);
    char char_of_initial_state = string_convert.at(0);
    if(result.size()>0)
    {
            //cout<<"Time to checkkkkkkkkkkk"<<endl;
            if(contains(result[result.size()-1],'1')&&contains(result[result.size()-1],'0')&&contains(result[result.size()-1],'2')&&contains(result[result.size()-1],'3'))
            {
               // cout<<"THISSSSS ISS ITTTT"<<endl;
                return result;
            }

    }

    vector<string>temp_path;
    vector<int>number_next_stage = List_of_states[initial_state].GetAllNumber();
    for(int i = 0 ;i<number_next_stage.size();i++)
    {
        string path = to_string(initial_state)+to_string(number_next_stage[i]);
        temp_path.push_back(path);
    }


    vector<string>temp_result;

    if(result.size()==0)
    {
        result = temp_path;
        //cout<<"this is okay";
    }
    else
    {

        int break_term=0;
        for(int i=0;i<result.size();i++)
        {
            //cout<<"for1";
            if(result[i].at(result[i].size()-1)==char_of_initial_state)
            {
                for(int j  = 0 ; j< temp_path.size();j++)
                {
                    string temp1 = result[i];
                    temp1.erase(temp1.end()-1);
                    string temp2 = temp1+ temp_path[j];
                    for(int z = 0 ;z<result.size();z++)
                    {
                        if(temp2==result[z])
                            break_term++;
                    }
                    temp_result.push_back(temp2);
                    //cout<<"A new path added to your vector"<<endl;
                }
            }
            if(break_term>=1)
                {
                    result.insert(result.end(),temp_result.begin(),temp_result.end());
                    return result;
                }

            //cout<<"Move to the next current path in the vector"<<endl;
        }
        //cout<<endl<<"DONE!!!"<<endl;
    }
    for(int i = 0 ; i<temp_result.size();i++)
    {
        result.push_back(temp_result[i]);
    }

   /*

    cout<<"here are current paths : ";
    for(int i = 0; i<result.size();i++)
    {
        cout<<result[i]<<" , ";
    }

    */

    for(int  i = 0 ; i< number_next_stage.size();i++)
    {
        vector<string>final_temp_result=Path_Generator(List_of_states,number_next_stage[i],result);

        for(int j = 0 ; j<final_temp_result.size();j++)
        {
            if(result[i]!=final_temp_result[j])
            {
                result.insert(result.end(),final_temp_result.begin()+j,final_temp_result.begin()+j+1);
            }
        }

    }
    /*
    cout<<"HERE ARE FINAL PATHS : ";
    for(int i = 0; i<result.size();i++)
    {
        cout<<result[i]<<" , ";
    }
    cout<<endl;
    */
    return result;
}

vector<string>NormalizePath(vector<string>result)
{
    int z=0;
    while(result.size()>0&&z<=3)
    {
        //normalize the vector
        for(int i = 0 ; i<result.size(); i++)
        {
            for(int j = 1; j<result.size();j++)
            {
                if(j!=i&&result[i]==result[j])
                {
                    result.erase(result.begin()+j,result.begin()+j+1);
                }
            }
        }
        z++;
    }

    return result;
}



bool FormulaCheck(vector<string>List_Of_Paths,string currentPath ,string atomic , vector<state>List_of_state, int pre_index, int post_index, int initial_state)
{
    if(pre_index!= post_index)
    {
        currentPath = List_Of_Paths[post_index];
    }
    pre_index = post_index;




    if(currentPath.at(0) == '\0')
        return false;
    else if(atomic.size()==1) // if atomic has only letter = label of i_state
        {
            string label = List_of_state[initial_state].GetLabel();
            for( int i = 0 ; i < label.size();i++)
            {
                if(atomic == label.substr(i,1))
                    return true;
            }
        }
    else if(atomic.at(0)=='n')// if atomic has the 'not'
    {
        atomic.erase(atomic.begin(),atomic.begin()+1);
        return 1 - FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state);
    }
    else if(atomic.at(0)=='X')
    {
        atomic.erase(atomic.begin(),atomic.begin()+1);
        currentPath.erase(currentPath.begin(),currentPath.begin()+1); //move to the next state in the path
        return FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state);
    }
    else if(atomic.at(0)=='F')
    {
        atomic.erase(atomic.begin(),atomic.begin()+1);
        if(FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state)==true)
            return true;
        else
        {
           currentPath.erase(currentPath.begin(),currentPath.begin()+1);
           return  FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state);
        }
    }
    else if(atomic.at(0)=='G')
    {
        atomic.erase(atomic.begin(),atomic.begin()+1);
        if(FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state)==true)
        {
            currentPath.erase(currentPath.begin(),currentPath.begin()+1);
            if(currentPath.at(0)=='\0')
                return true;
            else
                return FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state);
        }
        else
            return false;


    }
    else if(atomic.at(1)=='U')
    {
        if(FormulaCheck(List_Of_Paths,currentPath,atomic.substr(2,1),List_of_state,pre_index,post_index,initial_state)==true)
            return true;
        else
        {

            if(FormulaCheck(List_Of_Paths,currentPath,atomic.substr(0,1),List_of_state,pre_index,post_index,initial_state)==true)
            {
                currentPath.erase(currentPath.begin(),currentPath.begin()+1);
                if(currentPath.at(0)=='\0')
                    return true;
                else
                {
                    return FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state);
                }

            }
            else
                return false;

        }
    }
    else if(atomic.at(0)=='A')
    {
         atomic.erase(atomic.begin(),atomic.begin()+1);
        if(FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state)==true)
        {
            if(post_index == (List_Of_Paths.size()-1))
                return true;
            else
            {
                post_index++;
                return FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state);
            }
        }
        else
            return false;
    }
    else if(atomic.at(0)=='E')
    {
         atomic.erase(atomic.begin(),atomic.begin()+1);
        if(FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state)==true)
            return true;
        else
        {
            if(post_index==List_Of_Paths.size())
                return false;
            post_index++;
            return FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state);
        }
    }
    else if(atomic.at(1)=='E' && atomic.at(2)=='U') // if all the letters are not A E X F G
    {
        string temp = atomic;
        temp.erase(temp.begin()+1,temp.begin()+2);
        if(FormulaCheck(List_Of_Paths,currentPath,temp,List_of_state,pre_index,post_index,initial_state)==true) // if U is correct in this path return true
            return true;
        else // In this path U is not correct, move to other paths.
        {
            if(post_index==List_Of_Paths.size())
                return false;
            post_index++;
            return FormulaCheck(List_Of_Paths,currentPath,atomic,List_of_state,pre_index,post_index,initial_state);
        }
    }
    else
        return false;

}


void Determine(vector<state>List_of_states)
{
    int initial_state;
    string atomic;

    cout<<"Enter the initial state(enter the number of state): ";
    cin>>initial_state;
    cout<<"Enter the CTL formula: ";
    cin>>atomic;
    vector<string>list_of_paths;
    list_of_paths = Path_Generator(List_of_states,initial_state,list_of_paths);
    list_of_paths = NormalizePath(list_of_paths);
    cout<< "Possible paths : ";
    Print_Path(list_of_paths);
    if(FormulaCheck(list_of_paths,list_of_paths[0],atomic,List_of_states,0,0,initial_state)==true)
        cout<<endl<<"Answer: Yes"<<endl;
    else
        cout<<endl<<"Answer: No"<<endl;




}

int main()
{
    vector<state>List_of_States = Initialize();


    List_of_States = Set_transition(List_of_States);

    vector<string>result;
    result = Path_Generator(List_of_States,0,result);
    result = NormalizePath(result);
    Determine(List_of_States);


}

