#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
struct ANIMAL
{
    string name;
    int cage_number;
    int year_of_entry;
    bool is_rare;
    bool is_fed;
};

vector<ANIMAL> ANIMALS;
vector<string> outputs;
int CAGE_NUMBER = 0;

void add_output(string s)
{
    outputs.push_back(s);
}

void SET()
{
    int cage;
    cin >> cage;
    CAGE_NUMBER = cage;
}

void ADD()
{
    string name;
    int cage_number, year_of_entry, is_rare;
    cin >> name >> cage_number >> year_of_entry >> is_rare;
    bool x = false;
    if (name.length() < 2)
    {
        add_output("Invalid name");
        x = true;
    }
    for (int i = 0; i < ANIMALS.size(); i++)
    {
        if (ANIMALS[i].cage_number == cage_number)
        {
            add_output("Another animal is kept in this cage");
            x = true;
            break;
        }
    }
    if (cage_number < 1 || cage_number > CAGE_NUMBER)
    {
        add_output("This cage does not exist");
        x = true;
    }
    if (!x)
    {
        ANIMAL NEW_ANIMAL;
        NEW_ANIMAL.name = name;
        NEW_ANIMAL.cage_number = cage_number;
        NEW_ANIMAL.year_of_entry = year_of_entry;
        NEW_ANIMAL.is_rare = is_rare;
        NEW_ANIMAL.is_fed = false;
        ANIMALS.push_back(NEW_ANIMAL);
        add_output("The animal named " + name + " was added successfully");
    }
}

void SEARCH()
{
    string type;
    cin >> type;
    if (type == "name")
    {
        string name;
        bool found = false;
        cin >> name;
        for (int i = 0; i < ANIMALS.size(); i++)
        {
            if (ANIMALS[i].name == name)
            {
                add_output(ANIMALS[i].name + " " + to_string(ANIMALS[i].cage_number) + " " + to_string(ANIMALS[i].year_of_entry) + " " + to_string(ANIMALS[i].is_rare));
                found = true;
            }
        }
        if (!found)
            add_output("No animal was found");
    }
    else if (type == "cage_number")
    {
        int cage_number;
        cin >> cage_number;
        for (int i = 0; i < ANIMALS.size(); i++)
        {
            if (ANIMALS[i].cage_number == cage_number)
            {
                add_output(ANIMALS[i].name + " " + to_string(ANIMALS[i].cage_number) + " " + to_string(ANIMALS[i].year_of_entry) + " " + to_string(ANIMALS[i].is_rare));
                return;
            }
        }
        add_output("No animal was found");
    }
}

void LIST()
{
    if (ANIMALS.empty())
    {
        add_output("No animal was found");
    }
    else
    {
        for (int i = 0; i < ANIMALS.size(); i++)
        {
            add_output(ANIMALS[i].name + " " + to_string(ANIMALS[i].cage_number) + " " + to_string(ANIMALS[i].year_of_entry) + " " + to_string(ANIMALS[i].is_rare));
        }
    }
}

void DELETE()
{
    int cage_number;
    cin >> cage_number;
    for (int i = 0; i < ANIMALS.size(); i++)
    {
        if (ANIMALS[i].cage_number == cage_number)
        {
            add_output("The animal named " + ANIMALS[i].name + " was deleted successfully");
            ANIMALS.erase(ANIMALS.begin() + i);
            return;
        }
    }
    add_output("No animal was found");
}

void EDIT()
{
    int cage_number;
    string n, m;
    cin >> cage_number >> n;
    for (int i = 0; i < ANIMALS.size(); i++)
    {
        if (ANIMALS[i].cage_number == cage_number)
        {
            string oldname = ANIMALS[i].name;
            if (n == "name")
            {
                cin >> m;
                if (m.size() < 2)
                {
                    add_output("Invalid name");
                    return;
                }
                ANIMALS[i].name = m;
            }
            else if (n == "cage_number")
            {
                cin >> m;
                int new_cage_number = stoi(m);
                if (new_cage_number < 1 || new_cage_number > CAGE_NUMBER)
                {
                    add_output("This cage does not exist");
                    return;
                }
                for (int j = 0; j < ANIMALS.size(); j++)
                {
                    if (ANIMALS[j].cage_number == new_cage_number && ANIMALS[j].cage_number != cage_number)
                    {
                        add_output("Another animal is kept in this cage");
                        return;
                    }
                }
                ANIMALS[i].cage_number = new_cage_number;
            }
            else if (n == "year_of_entry")
            {
                cin >> m;
                ANIMALS[i].year_of_entry = stoi(m);
            }
            else if (n == "is_rare")
                ANIMALS[i].is_rare = !ANIMALS[i].is_rare;
            else if (n == "is_fed")
                ANIMALS[i].is_fed = !ANIMALS[i].is_fed;
            add_output("The animal named " + oldname + " was edited successfully");
            return;
        }
    }
    add_output("No animal was found");
}

bool comparesort(ANIMAL a, ANIMAL b)
{
    if (a.name == b.name)
        return a.cage_number < b.cage_number;
    return a.name < b.name;
}

void SORT()
{
    sort(ANIMALS.begin(), ANIMALS.end(), comparesort);
}


bool comparefed(ANIMAL a, ANIMAL b)
{
    if (a.is_rare != b.is_rare)
        return a.is_rare > b.is_rare;
    return a.year_of_entry < b.year_of_entry;
}

void FEED()
{
    int a;
    cin >> a;
    vector<ANIMAL> not_fed;
    for (int i = 0; i < ANIMALS.size(); i++)
    {
        if (!ANIMALS[i].is_fed)
        {
            not_fed.push_back(ANIMALS[i]);
        }
    }
    sort(not_fed.begin(), not_fed.end(), comparefed);
    int b = not_fed.size();
    for (int i = 0; i < a && i < b; i++)
    {

        for (int j = 0; j < ANIMALS.size(); j++)
        {
            if (ANIMALS[j].cage_number == not_fed[i].cage_number)
            {
                ANIMALS[j].is_fed = true;
                add_output("The animal named " + ANIMALS[j].name + " was fed");
                break;
            }
        }
    }
}

void SAVE()
{
    string filename;
    cin >> filename;
    ofstream out(filename);
    for (int i = 0; i < ANIMALS.size(); i++)
    {
        out << ANIMALS[i].name << " " << ANIMALS[i].cage_number << " " << ANIMALS[i].year_of_entry << " " << ANIMALS[i].is_rare << " " << ANIMALS[i].is_fed << endl;
    }
    out.close();
    add_output("Animals were saved successfully");
}

void LOAD()

{
    string filename;
    cin >> filename;
    ifstream in(filename);
    if (!in.is_open())
    {
        add_output("The file does not exist");
        return;
    }
    ANIMAL c;
    ANIMALS.clear();
    while (in >> c.name >> c.cage_number >> c.year_of_entry >> c.is_rare >> c.is_fed)
    {
        ANIMALS.push_back(c);
    }
    in.close();
    add_output("Animals were loaded successfully");
}

int main()
{
    string order;
    while (cin >> order)
    {
        if (order == "EXIT")
            break;
        if (order == "SET")
            SET();
        else if (order == "ADD")
            ADD();
        else if (order == "SEARCH")
            SEARCH();
        else if (order == "LIST")
            LIST();
        else if (order == "DELETE")
            DELETE();
        else if (order == "EDIT")
            EDIT();
        else if (order == "SORT")
            SORT();
        else if (order == "FEED")
            FEED();
        else if (order == "SAVE")
            SAVE();
        else if (order == "LOAD")
            LOAD();
    }
    for (int i = 0; i < outputs.size(); i++)
    {
        cout << outputs[i] << endl;
    }

    return 0;
}