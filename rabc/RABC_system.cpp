#include<iostream>
#include<vector>
using namespace std;
class Role
{
private:
    string name;
    vector<string>list_of_permission;
    string session;
    vector<bool>Rank;
public:
    Role(){}
    Role(string name, string session)
    {
        this->name = name;
        this->session=session;
    }
    void SetInfo(string name, string session)
    {
        this->name = name;
        this->session=session;
    }
    void AddPermission(string permission)
    {
        list_of_permission.push_back(permission);
    }
    void SetUpRank(bool PCM, bool Faculty, bool Lecturer, bool Student, bool TA,bool PTEmployee )
    {
        Rank.push_back(PCM);
        Rank.push_back(Faculty);
        Rank.push_back(Lecturer);
        Rank.push_back(TA);
        Rank.push_back(Student);
        Rank.push_back(PTEmployee);

    }
    vector<bool> GetRank()
    {
        return this->Rank;
    }
    Role* operator=(Role other_role)
    {
        this->name = other_role.name;
        this->session = other_role.session;
        this->Rank = other_role.Rank;
        this->list_of_permission=other_role.list_of_permission;
        return this;
    }
    string GetSession()
    {
        return this->session;
    }
    string GetName()
    {
        return this->name;
    }
    vector<string> GetPermission()
    {
        return this->list_of_permission;
    }

};
class User
{
private:
    vector<Role*>list_of_role;
    string name;
    vector<string> list_of_sessions;
    vector<string> list_of_permissions;
public:
    User(){}
    User(string name,string session)
    {
        this->name = name;
        list_of_sessions.push_back(session);
    }
    void AddRole(Role* other_role)
    {
        list_of_role.push_back(other_role);
    }
    void AddSession(string session)
    {
        list_of_sessions.push_back(session);
    }
    vector<string> GetSession()
    {
        return list_of_sessions;
    }
    string GetName()
    {
        return this->name;
    }
    vector<Role*> GetRole()
    {
        return this->list_of_role;
    }

};
void Determine(vector<User*>list_of_user,vector<Role*>list_of_role)
{
    string input_user_name;
    string input_permission;
    cout<<"Input the user : ";
    cin>>input_user_name;
    cout<<"Input the permission: ";
    cin>>input_permission;
    vector<string>List_of_permission;
    vector<Role*>List_of_this_user_role;
    vector<bool>list_of_rank;
    vector<string>User_session;
    string Role_session;

    for(int i = 0 ; i<list_of_user.size();i++)
    {

        if(list_of_user[i]->GetName()==input_user_name)
        {
            User_session=list_of_user[i]->GetSession();
            List_of_this_user_role=list_of_user[i]->GetRole();
            for(int j = 0; j <List_of_this_user_role.size();j++)
            {
                list_of_rank=List_of_this_user_role[j]->GetRank();
                for(int z = 0; z<list_of_rank.size();z++)
                {
                    bool compare_result=0;
                    if(list_of_rank[z]==1)
                    {
                        for(int x = 0;x<User_session.size();x++)
                        {
                            if(User_session[x]==list_of_role[z]->GetSession())
                                compare_result=1;

                        }
                        if(compare_result==1)

                        {
                        vector<string>temp = list_of_role[z]->GetPermission();
                        List_of_permission.insert(end(List_of_permission),begin(temp),end(temp));
                        }
                    }
                }
                cout<<endl;
            }
        }

    }
    bool final_result=0;
    for(int i = 0 ; i<List_of_permission.size();i++)
    {
        if(List_of_permission[i]==input_permission)
        {
            final_result=1;
        }
    }
    cout<<"Answer: ";
    if(final_result)
    {
        cout<<"Yes"<<endl;
    }
    else
    {
        cout<<"No"<<endl;
    }

}
int main()
{
    //Construct and adding permission for each role
    Role PCM("PCMember","s1");
    PCM.AddPermission("delete_course2");

    Role Faculty("Faculty","s1");
    Faculty.AddPermission("delete_course1");
    Faculty.AddPermission("modify_course2");

    Role Lecturer("Lecturer","s1");
    Lecturer.AddPermission("modify_course2");

    Role Student("Student","s2");
    Student.AddPermission("register_to_course1");

    Role TA("TA","s2");
    TA.AddPermission("modify_course3");

    Role PTE("PTEmployee","s2");

    //Construct the hierarchy
    PCM.SetUpRank(1,1,1,1,1,1);
    Faculty.SetUpRank(0,1,0,1,0,0);
    Lecturer.SetUpRank(0,0,1,1,0,1);
    Student.SetUpRank(0,0,0,0,1,0);
    TA.SetUpRank(0,0,0,1,0,0);
    //Construct the user and role
    User Alice("Alice","s1");
    Alice.AddSession("s2");
    Alice.AddRole(&Lecturer);

    User Bob("Bob","s2");
    Bob.AddRole(&PCM);

    User Oscar("Oscar","s1");
    Oscar.AddSession("s2");
    Oscar.AddRole(&TA);

    User Charlie("Charlie","s1");
    Charlie.AddRole(&Student);
    Charlie.AddRole(&TA);
    //To work with the function we need to grab all the data into array, and throw that two the function parameters
    vector<User*>list_of_user;
    list_of_user.push_back(&Bob);
    list_of_user.push_back(&Alice);
    list_of_user.push_back(&Oscar);
    list_of_user.push_back(&Charlie);
    vector<Role*>list_of_role;
    list_of_role.push_back(&PCM);
    list_of_role.push_back(&Faculty);
    list_of_role.push_back(&Lecturer);
    list_of_role.push_back(&Student);
    list_of_role.push_back(&TA);
    list_of_role.push_back(&PTE);




    Determine(list_of_user,list_of_role);




}
