#include<iostream>
#include<vector>
using namespace std;
class Object
{
private:
    string name;
    bool own;
    bool read;
    bool write;
    bool execute;
public:
    Object(){}
    Object(string name)
    {
        this->name=name;
    }
    void Set_Auth(bool o, bool r, bool w, bool e)
    {
        this->own=o;
        this->read=r;
        this->write=w;
        this->execute=e;
    }
    bool GetAuthentication(string action)
    {
        if(action == "own")
            return this->own;
        else if(action == "read")
            return this->read;
        else if(action == "write")
            return this->write;
        else if(action=="execute")
            return this->execute;
        else
            return 0;

    }
    string GetName()
    {
        return this->name;
    }

};
 class Subject
 {
 private:
    vector<Object>list_of_object;
 public:
    Subject(){}
    void Add_Object(Object object)
    {
        list_of_object.push_back(object);
    }
    void Set_Auth(string object_name,bool o, bool r, bool w, bool e)
    {
        for( int i = 0; i <list_of_object.size();i++)
        {
            if(list_of_object[i].GetName()==object_name)
                list_of_object[i].Set_Auth(o,r,w,e);
        }
    }
    bool GetAuth(string action, string object_name)
    {
        for( int i = 0; i <list_of_object.size();i++)
        {
            if(list_of_object[i].GetName()==object_name)
                return list_of_object[i].GetAuthentication(action);
        }
    }
    friend bool Determine(Subject subject,string action, string object);


 };
 bool Determine(Subject subject, string action, string object)
 {
     return subject.GetAuth(action, object);
 }
 int main()
 {
     Object F1("File 1");
     Object F2("File 2");
     Object F3("File 3");
     Object F4("File 4");
     Object F5("File 5");

     Subject Alice;
     Alice.Add_Object(F1);
     Alice.Add_Object(F2);
     Alice.Add_Object(F3);
     Alice.Add_Object(F4);
     Alice.Add_Object(F5);

     Subject Bob;
     Bob.Add_Object(F1);
     Bob.Add_Object(F2);
     Bob.Add_Object(F3);
     Bob.Add_Object(F4);
     Bob.Add_Object(F5);

      Subject Maco;
     Maco.Add_Object(F1);
     Maco.Add_Object(F2);
     Maco.Add_Object(F3);
     Maco.Add_Object(F4);
     Maco.Add_Object(F5);

     Subject Oscar;
     Oscar.Add_Object(F1);
     Oscar.Add_Object(F2);
     Oscar.Add_Object(F3);
     Oscar.Add_Object(F4);
     Oscar.Add_Object(F5);

     Subject Mary;
     Mary.Add_Object(F1);
     Mary.Add_Object(F2);
     Mary.Add_Object(F3);
     Mary.Add_Object(F4);
     Mary.Add_Object(F5);

     Alice.Set_Auth("File 1",1,1,1,1);
     Alice.Set_Auth("File 2",0,1,1,0);
     Alice.Set_Auth("File 3",0,0,0,0);
     Alice.Set_Auth("File 4",0,1,0,1);
     Alice.Set_Auth("File 5",0,0,1,0);

     Bob.Set_Auth("File 1",0,0,0,1);
     Bob.Set_Auth("File 2",0,1,0,0);
     Bob.Set_Auth("File 3",1,1,1,1);
     Bob.Set_Auth("File 4",0,0,1,0);
     Bob.Set_Auth("File 5",0,0,0,0);

     Oscar.Set_Auth("File 1",0,0,0,0);
     Oscar.Set_Auth("File 2",1,1,1,1);
     Oscar.Set_Auth("File 3",0,0,0,0);
     Oscar.Set_Auth("File 4",0,0,0,1);
     Oscar.Set_Auth("File 5",0,0,0,0);

     Maco.Set_Auth("File 1",0,1,0,0);
     Maco.Set_Auth("File 2",0,0,0,0);
     Maco.Set_Auth("File 3",0,0,1,0);
     Maco.Set_Auth("File 4",1,1,1,1);
     Maco.Set_Auth("File 5",0,0,0,1);

     Mary.Set_Auth("File 1",0,0,0,0);
     Mary.Set_Auth("File 2",0,1,0,0);
     Mary.Set_Auth("File 3",0,1,0,0);
     Mary.Set_Auth("File 4",0,1,0,1);
     Mary.Set_Auth("File 5",1,1,1,1);

     cout<<Determine(Mary,"read","File 2")<<endl;
     cout<<Determine(Alice,"write","File 3")<<endl;
 }
