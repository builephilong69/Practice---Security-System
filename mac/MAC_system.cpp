#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Classification
{
private:
    string level;
    int level_to_number;
public:
    Classification(){}
    Classification(string level)
    {
        this->level=level;
        if(level =="TS")
            this->level_to_number=4;
        else if(level=="S")
            this->level_to_number=3;
        else if(level=="C")
            this->level_to_number=2;
        else if(level=="U")
            this->level_to_number=1;
        else
            this->level_to_number=0; // in wrong case
    }
    void Set_Classification_Level(string level)
    {
        this->level=level;
        if(level =="TS")
            this->level_to_number=4;
        else if(level=="S")
            this->level_to_number=3;
        else if(level=="C")
            this->level_to_number=2;
        else if(level=="U")
            this->level_to_number=1;
        else
            this->level_to_number=0; // in wrong case
    }
    int C_level_to_number()
    {
        return this->level_to_number;
    }
    string Get_Level()
    {
        return this->level;
    }
};
class Object
{
private:
    string name;
    Classification object_Classification_level;
public:
    Object(){}
    Object(string name, string C_level)
    {
        this->name=name;
        object_Classification_level.Set_Classification_Level(C_level);

    }
    void Set_Classification_Level(string C_level)
    {
        object_Classification_level.Set_Classification_Level(C_level);
    }
    int C_level_to_number()
    {
        return object_Classification_level.C_level_to_number();
    }
    string Get_Level()
    {
        return object_Classification_level.Get_Level();
    }
    string GetName()
    {
        return this->name;
    }
    void Set_Level(string level)
    {
        this->object_Classification_level.Set_Classification_Level(level);
    }
    void operator=(Object other)
    {
        return Set_Level(other.Get_Level());
    }

};
 class Subject
 {
 private:
    Classification subject_Classification_level;
    string name;
 public:
    Subject(){}
    Subject(string name,string level)
    {
        this->name = name;
        subject_Classification_level.Set_Classification_Level(level);
    }
    void Set_Level(string level)
    {
        subject_Classification_level.Set_Classification_Level(level);
    }

    int C_level_to_number()
    {
        return subject_Classification_level.C_level_to_number();
    }
    string Get_Level()
    {
        return subject_Classification_level.Get_Level();
    }
    string GetName()
    {
        return this->name;
    }
    void operator=( Subject other)
    {
        return Set_Level(other.Get_Level());
    }


 };
 int main()
 {
     //Initialize the table:
     Object F1("File1","TS");
     Object F2("File2","TS");
     Object F3("File3","U");
     Object F4("File4","C");
     Object F6("File6","TS");
     Object F5("File5","S");
     Object P1("Program1","C");
     Object P2("Program2","TS");
     Object P3("Program3","S");
     vector<Object>list_of_object;
     list_of_object.push_back(F1);
     list_of_object.push_back(F2);
     list_of_object.push_back(F3);
     list_of_object.push_back(F4);
     list_of_object.push_back(F5);
     list_of_object.push_back(F6);
     list_of_object.push_back(P1);
     list_of_object.push_back(P2);
     list_of_object.push_back(P3);


    Subject S1("Alice","TS");
    Subject S2("Bob","S");
    Subject S3("Marco","TS");
    Subject S4("Mary","U");
    Subject S5("Peter","C");
    vector<Subject>list_of_subject;
    list_of_subject.push_back(S1);
    list_of_subject.push_back(S2);
    list_of_subject.push_back(S3);
    list_of_subject.push_back(S4);
    list_of_subject.push_back(S5);





     //Determine

        Object object;
        string object_name;
        Subject subject;
        string subject_name;
        string action;
        cout<<"Enter the Subject's name: "<<endl;;
        cin>>subject_name;
        cout<<"Enter the  Object's name: "<<endl;
        cin>>object_name;
        cout<<"Enter the Action: "<<endl;
        cin>>action;


        for( int  i = 0 ; i<list_of_subject.size();i++)
        {
            if(subject_name==list_of_subject[i].GetName())
            {
                subject = list_of_subject[i];
            }
        }
        for( int  i = 0 ; i<list_of_object.size();i++)
        {
            if(object_name==list_of_object[i].GetName())
            {
                object = list_of_object[i];

            }
        }

        if(action =="write")
        {
            if(object.C_level_to_number()>=subject.C_level_to_number())
                cout<<"Accepted"<<endl;
            else
                cout<<"Denied"<<endl;
        }
        else if(action == "read")
        {
            if(subject.C_level_to_number()>=object.C_level_to_number())
                cout<<"Accepted"<<endl;
            else
                cout<<"Denied"<<endl;
        }
        else
        {
            cout<<"Wrong action form"<<endl;
        }

 }

