#include<iostream>
#include<vector>
using namespace std;
class Role
{
public:
    string name;
    vector<string>permission;
    vector<string>Session;

    Role(){}
    Role(string name)
    {
        this->name= name;
    }
    void SetSession(string s)
    {
        Session.push_back(s);
    }
    void SetPermission(string p)
    {
        permission.push_back(p);
    }
     string GetName()
    {
        return this->name;
    }
    vector<string> GetPermission()
    {
        return this->permission;
    }
    vector<string> GetSession()
    {
        return this->Session;
    }
};
class User
{
public:
    string name;
    vector<Role*>ListOfRole;
    vector<string>Session;

    User(){}
    User(string name)
    {
        this->name= name;
    }
    void SetRole(Role* role)
    {
        ListOfRole.push_back(role);
    }
    void SetSession(string s)
    {
        Session.push_back(s);
    }

    string GetName()
    {
        return this->name;
    }
    vector<string> GetRoleName()
    {
        vector<string> temp;
        for(int i=0;i<ListOfRole.size();i++)
            temp.push_back(ListOfRole[i]->GetName());
        return temp;
    }
    vector<string> GetSession()
    {
        return this->Session;
    }
};
bool Role_Hiearchy(string role1, string role2)
{
    if(role1 == role2)
        return true;
    else if(role1 == "Principal")
    {
        if(role2 =="PCMember")
            return false;
        else
            return true;
    }
    else if(role1=="Dean")
    {
        if(role2=="Principal"||role2=="PCMember")
            return false;
        else
            return true;
    }
    else if(role1=="Falculty")
    {
        if(role2=="Student")
            return true;
        else
            return false;
    }
    else if(role1=="Lecturer")
    {
        if(role2=="TA"||role2=="PTEmployee")
            return true;
        else
            return false;
    }
    else if(role1=="PCMember")
    {
        if(role2=="Lecturer"||role2=="TA"||role2=="PTEmployee")
            return true;
        else
            return false;
    }
    else
        return false;
}
void Assign_and_Revoke(vector<User*>ListOfUser,vector<Role*>ListOfRole)
{
    for(int i=0;i<ListOfUser.size();i++)
    {
        vector<string>Users_Role= ListOfUser[i]->GetRoleName();
        for(int j = 0 ; j <Users_Role.size();j++)
        {
            //If they are students, then there exists a path for them to become TA
            if(Role_Hiearchy(Users_Role[j],"Student"))
            {
                for(int z=0;z<ListOfRole.size();z++)
                {
                    if(ListOfRole[z]->GetName()=="TA")
                    {
                        ListOfUser[i]->SetRole(ListOfRole[z]);
                    }
                }
            }
        }
    }
    for(int i=0;i<ListOfUser.size();i++)
    {
        vector<string>Users_Role= ListOfUser[i]->GetRoleName();
        for(int j = 0 ; j <Users_Role.size();j++)
        {
            //If they are TA, then there is a path for them to become lecturer
            if(Role_Hiearchy(Users_Role[j],"TA"))
            {
                for(int z=0;z<ListOfRole.size();z++)
                {
                    if(ListOfRole[z]->GetName()=="Lecturer")
                    {
                        ListOfUser[i]->SetRole(ListOfRole[z]);
                    }
                }
            }
        }
    }
    for(int i=0;i<ListOfUser.size();i++)
    {
        vector<string>Users_Role= ListOfUser[i]->GetRoleName();
        bool gate1;
        bool gate2;
        //If they are lecturer and not faculty, there exists a path for them to become Dean
        for(int j = 0 ; j <Users_Role.size();j++)
        {
            if(Role_Hiearchy(Users_Role[j],"Lecturer"))
            {
                gate1=1;
            }
            if(Role_Hiearchy(Users_Role[j],"Faculty"))
            {
                gate2=1;
            }
        }
        if(gate1==1&&gate2==0)
        {
            for(int z=0;z<ListOfRole.size();z++)
            {
                if(ListOfRole[z]->GetName()=="Dean")
                {
                    ListOfUser[i]->SetRole(ListOfRole[z]);
                }
            }
        }
    }
}

void PrintThings(vector<string>List)
{
    for(int i = 0 ; i<List.size();i++)
    {
        cout<<List[i]<<" ";
    }
}
vector<string> Permission_to_Rolename(vector<Role*>ListOfRole,string Input_permission)
{
    vector<string>temp;
    for(int i = 0 ; i<ListOfRole.size();i++)
    {
        vector<string>Role_permission=ListOfRole[i]->GetPermission();
        for(int j=0;j<Role_permission.size();j++)
        {
            if(Role_permission[j]==Input_permission)
            {
                temp.push_back(ListOfRole[i]->GetName());
            }
        }
    }
    return temp;
}
bool Determine(vector<User*>ListOfUsers,vector<Role*>ListOfRole, string Input_username, string Input_permission)
{
    for(int i = 0 ;i<ListOfUsers.size();i++)
    {
        if(ListOfUsers[i]->GetName()==Input_username)
        {
            vector<string>Per_to_name=Permission_to_Rolename(ListOfRole,Input_permission);
            vector<string>User_to_role=ListOfUsers[i]->GetRoleName();
            for(int j = 0 ; j<Per_to_name.size();j++)
            {
                for(int z=0;z<User_to_role.size();z++)
                {
                    if(User_to_role[z]==Per_to_name[j])
                    {
                        vector<string>User_session=ListOfUsers[i]->GetSession();
                        vector<string>Role_session;
                        // find role session by its name;
                        for(int a = 0 ; a<ListOfRole.size();a++)
                        {
                            if(Per_to_name[j]==ListOfRole[a]->GetName())
                                Role_session=ListOfRole[a]->GetSession();
                        }
                        // check if role sesion == user session
                        for(int b=0;b<User_session.size();b++)
                        {
                            for(int c = 0; c<Role_session.size();c++)
                            {
                                if(User_session[b]==Role_session[c])
                                    return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
int main()
{
    //Role
    Role r1("Faculty");
    r1.SetPermission("delete_course1");
    r1.SetPermission("modify_course2");
    r1.SetSession("s1");

    Role r2("Lecturer");
    r2.SetPermission("modify_course1");
    r2.SetPermission("modify_course2");
    r2.SetSession("s2");

    Role r3("TA");
    r3.SetPermission("modify_course3");
    r3.SetSession("s2");

    Role r4("PCMember");
    r4.SetPermission("delete_course1");
    r4.SetSession("s1");

    Role r5("Student");
    r5.SetPermission("register_to_course1");
    r5.SetPermission("register_to_course3");
    r5.SetSession("s2");

    Role r6("Dean");
    r6.SetPermission("modify_course3");
    r6.SetSession("s3");
    r6.SetSession("s1");

    Role r7("Principal");
    r7.SetPermission("delete_course2");
    r7.SetSession("s1");
    r7.SetSession("s2");

    Role r8("PTEmployee");
    r8.SetPermission("modify_course1");
    r8.SetSession("s3");

        vector<Role*>ListOfRole;
        ListOfRole.push_back(&r1);
        ListOfRole.push_back(&r2);
        ListOfRole.push_back(&r3);
        ListOfRole.push_back(&r4);
        ListOfRole.push_back(&r5);
        ListOfRole.push_back(&r6);
        ListOfRole.push_back(&r7);
        ListOfRole.push_back(&r8);

    //User
    User u1("Bob");
    u1.SetRole(&r4);
    u1.SetSession("s2");

    User u2("Alice");
    u2.SetRole(&r2);
    u2.SetSession("s1");

    User u3("Oscar");
    u3.SetRole(&r3);
    u3.SetSession("s1");
    u3.SetSession("s2");

    User u4("Charlie");
    u4.SetRole(&r5);
    u4.SetRole(&r3);
    u4.SetSession("s1");
    u4.SetSession("s3");

    User u5("Mary");
    u5.SetRole(&r6);
    u5.SetSession("s1");
    u5.SetSession("s2");

    User u6("Peter");
    u6.SetRole(&r7);
    u6.SetSession("s1");
    u6.SetSession("s2");

    User u7("John");
    u7.SetRole(&r8);
    u7.SetSession("s3");

    User u8("Marco");
    u8.SetRole(&r1);
    u8.SetSession("s1");

        vector<User*>ListOfUser;
        ListOfUser.push_back(&u1);
        ListOfUser.push_back(&u2);
        ListOfUser.push_back(&u3);
        ListOfUser.push_back(&u4);
        ListOfUser.push_back(&u5);
        ListOfUser.push_back(&u6);
        ListOfUser.push_back(&u7);
        ListOfUser.push_back(&u8);
    Assign_and_Revoke(ListOfUser,ListOfRole);


    string Input_username;
    string Input_permission;
    cout<<"Input the user name: ";
    cin>>Input_username;
    cout<<"Input the permission: ";
    cin>>Input_permission;
    if(Determine(ListOfUser,ListOfRole,Input_username,Input_permission))
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;


}
