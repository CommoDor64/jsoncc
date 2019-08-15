#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>
#include <vector>
#include <map>
using namespace std;

const char CURLY_BRACES_OPEN = '{';
const char CURLY_BRACES_CLOSE = '}';
const char BRACKET = '\"';
const char COMMA = ',';
const char COLON = ':';

class json
{
private:
public:
    string jsonString;
    void compressJson();
    bool readAndVerify(std::ifstream &file);
    void traverse();
};

void json::compressJson()
{
    string compressedJson("");
    for (char &c : json::jsonString)
    {
        if (c == ' ')
        {
            continue;
        }
        compressedJson += c;
    }
    json::jsonString = compressedJson;
}

bool json::readAndVerify(ifstream &file)
{
    string line;
    stack<char> veriStack;
    while (getline(file, line))
    {
        for (char &c : line)
        {
            switch (c)
            {
            case CURLY_BRACES_OPEN:
                veriStack.push(c);
                break;
            case CURLY_BRACES_CLOSE:
                if (veriStack.empty())
                {
                    json::jsonString = "";
                    return false;
                }
                else
                    veriStack.pop();
                break;
            default:
                break;
            }
            json::jsonString += c;
        }
    }
    if (veriStack.empty())
        return true;
    json::jsonString = "";
    return false;
}

void json::traverse()
{
    bool isField = true;
    string field, value = "";
    map<string, string> treeLevel;
    for (char &c : json::jsonString)
    {
        switch (c)
        {
        case CURLY_BRACES_OPEN:
            break;
        case BRACKET:
            break;
        case COLON:
            isField = !isField;
            break;
        case COMMA:
        case CURLY_BRACES_CLOSE:
            if (treeLevel.find(field) == treeLevel.end())
                treeLevel[field] = value;
            field = "";
            value = "";
            isField = !isField;
            break;
        default:
            if (isField)
            {
                field += c;
                continue;
            }
            value += c;
            break;
        }
    }
}

void recTraverse(vector<string> subJson)
{
}

int main(int argc, char *argv[])
{
    json jsonParser;
    string line;
    ifstream file("test.test.json");
    if (file.is_open())
    {
        jsonParser.readAndVerify(file);
        jsonParser.compressJson();
        jsonParser.traverse();
    }
    file.close();
    return 0;
}
