#include <bits/stdc++.h>
using namespace std;
#include <cstring>
#define ll long long int


struct node
{
    string label = "";     
    string value = "";        
    vector<node> children;   
    int poswrtpar = -1 ;   
    node* parent = NULL;
    pair<int,int> range = {-1,-1};
    int version = -1;

};
vector<node> nodelist;

void print_node(node n)
{
    cout<<"+++++++++++++++++++++"<<endl;
    cout<<"label= "<<n.label<<endl;
    cout<<"value= "<<n.value<<endl;
    cout<<"version= "<<n.version<<endl;
    cout<<"range= "<<n.range.first<<" "<<n.range.second<<endl;


    
    if(n.parent != NULL)
    {
       //cout<<"Parent = "<<n.parent->label<<" "<<n.parent->value<<endl;
       cout<<"Parent = "<<(*(n.parent)).version<<endl;
       
    }
    else
        cout<<"Root"<<endl;
    cout<<"======================"<<endl;
    
     
}

struct editAction
{
    string typeOfAction = "" ;          
    node insertedNode;  
    node deletedNode;

    map<node,vector<node>> moveTree;
    map<node,vector<node>> insertTree;
    map<node,vector<node>> deleteTree;

    node moveFrom;
    node moveTo;
    int movetopos = 1;

    node insertTo ;
    int insertpos = -1;


    int isUseful = -1;           
    int initialVersion = -1;
    set<node> span;

};

map<node,vector<editAction>> nodeToEditAction ; //list of editActions associated with every node

struct cmp
{
    bool operator()(const tuple<int,int,node> &p1, const tuple<int,int,node> &p2) const
    {
        return get<0>(p1) > get<0>(p2) ;
    }  
};


void readSpaces(int& space,string nodeText,int& i)
{
    space = 0;
    for(;i<(int)nodeText.length();i++)
    {
        char c = nodeText[i];
        if(c!=' ')
        break;
        space++;

    }
}

pair<string,string> readLabel(string nodeText, int& i)
{
    string label="";
    string end="";
    for(;i<(int)nodeText.length();i++)
    {
        if(nodeText[i] == ' ')
        {
            end = " ";
            i=i+1;
            break;
        }
        if(nodeText[i] == ':')
        {
            end = ":";
            i=i+2;
            break;
        }
        label = label+nodeText[i];
    }
    return make_pair(label,end);
}
string readComment(string nodetext,int& i)
{
    string val="";
    int commclose;
    int j;
    for(j=(int)nodetext.length()-1;j>=0;j--)
    {
        if(nodetext[j]==')')
        break;
    }

    for(;i<=j;i++)
    val=val+nodetext[i];

    i=j+2;
    return val;
}
string readValue(string nodeText,int& i )
{
    string val="";
    int j=i; int last_quote;
    for(;j<(int)nodeText.length();j++)
    {
        char c  = nodeText[i];
        if(c=='"')
        last_quote = j;
    }
    if( nodeText[i] == '"')
    {
        i=i+1;
        for(;i<last_quote;i++)
        val+=nodeText[i];
        i=i+2; //1 for the closing quote and other for the following space
    }
    else{
    for(;i<(int)nodeText.length();i++)
    {
        char c  = nodeText[i];
        if(c==' ')
        break;
        val = val+c;
    }
    }
    return val;
}                                          

pair<int,int> readRange(string nodeText,int& i)
{
    int first,last;
    string num;
    for(;i<(int)nodeText.length();i++)
    {
        char c=nodeText[i];
        if(c=='[')
        {
            i++;
            for(;i<(int)nodeText.length();i++)
            {
                num=num+nodeText[i];
            }
            break;
        }
    }
    vector<int> v;
    stringstream NUM(num);
    string s;
    while(getline(NUM, s, ','))
    {
        v.push_back(stoi(s));
    }
    return make_pair(v[0],v[1]);

}

void tokenize(string contents,vector<string>& editBlock,char* delim)
{
    char* str= (char*)contents.c_str();
    char *token = strtok(str,delim);
    while (token)  
    {
        editBlock.push_back(token);
        token = strtok(NULL,delim);
    }
}

/*
void parseEditActions(vector<editAction> editActions,ifstream editScriptfile)
{
    string contents = "";
    char c;
    while(editScriptfile>>c)
        contents+=c;
    vector<string> editBlocks;
    tokenize(contents,editBlocks,"===");


    for (auto actions : editBlocks)
    {
        vector<string> action_;
        tokenize(actions,action_,"---");

        if(action_[0] == "match")
            continue;
        editAction e;
        if(action_[0] == "insert-node")
        {
            e.typeOfAction = "insert-node";
            node n ;
            n.
            e.insertedNode =  
            e.span = 
        }

            
        if(action_[0] == 'insert-tree"):
            breakIntoAtoms(editActions,action_[0])
        
        if(action_[0] == 'delete-node'):

        if(action_[0] == 'delete-tree'):
            breakIntoAtoms(editActions,action_[0])
 
        if(action_[0] == 'move-tree'):
            breakIntoAtoms(editActions,action_[0])
    }
}

void associateEditActionsWithNode()
{
    for(x : editActions)
    {
        for(n : x.span)
        {
            n.push_back(x);
        }
    }

}
*/
void find_parent(vector<tuple<int,int,node>>& tree,int space,node* curr,vector<node> nodelist)
{
    assert(tree.size()>0);
    assert(tree.size() == nodelist.size());
    int it_nl=0;
    for(auto it = tree.end()-1; it>=tree.begin(); it--,it_nl++)
    {
        if(get<1>(*it) < space)
        {
            curr->parent = &nodelist[it_nl];
            //cout<<(*(curr->parent)).label<<endl;
            break;
        }
    }
}
void parseAST(map<node,vector<node>>& ast , node& root ,string astFile)
{
    vector<string> lines;
    string currLine;
    vector<tuple<int,int,node>> potParentSet; //line number , number of spaces , node
    tokenize(astFile,lines,"\n");
    int lineno=0;
    string nodeText;
    for(int i_lines = 0;i_lines<(int)lines.size();i_lines++)
    {
        lineno++;
        currLine = lines[i_lines];
        //cout<<currLine<<endl;
        int space = 0;
        int zone = 0;   //0 -> leading spaces , 1-> label name, 2 -> value , 3-> range
        struct node curr;
        bool isroot = false;

        for (int i=0;i<currLine.length();i++)
        {
            char c = currLine[i];
            if (zone==0 && c!= ' ') //no leading spaces -> root
            {
                isroot = true;
                zone = 1;
            }
            if (zone==0 && c == ' ')
            {
                readSpaces(space,currLine,i);
                zone=1;
            }

            if (zone==1)
            {
               pair<string,string> info = readLabel(currLine,i);
               if(info.second == ":")
               zone=2;
               else
               zone=3;
               curr.label=info.first;
            }
            if (zone ==2)
            {
                string value="";
                if(curr.label == "comment")
                value = readComment(currLine,i);
                else
                value = readValue(currLine,i);
                zone = 3;
                curr.value = value;
            }
            if (zone == 3)
            {
                pair<int,int> range = readRange(currLine,i);
                zone = 100;
                curr.range.first = range.first;
                curr.range.second = range.second;
            }
        }
        if(isroot)
            root = curr;
        else
        {
            find_parent(potParentSet,space,&curr,nodelist);
        }
        potParentSet.push_back(make_tuple(lineno,space,curr));
        nodelist.push_back(curr);
        print_node(curr);
        /*
        for(auto q: nodelist)
        print_node(q);
        */
    }
}

int main()
{
    nodelist.reserve(1000);
    ifstream f;
    f.open("ast_commit_history/gcd/PAZN9YJOWYE1.1.ml");
    string str ; string l;
    while(getline(f,l))
    {
        str = str + l + "\n";
    }
    map<node,vector<node>> ast; node root;
    parseAST(ast,root,str);
    return 0;
}