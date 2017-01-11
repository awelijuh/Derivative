#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;
string s;
vector<int> prior;
string Factar(int,int,int);
string prois(int,int);
string cop(int,int);
bool Trivial(int,int);
bool ConstDetect(int l,int r);
string Multiply(string s1,string s2);
string Multiply(string s1,string s2,string s3);

string cop(int l,int r)
{
    if(l>r) return "";
    return s.substr(l,r-l+1);
}

string cops(int l,int r)
{
    if(l>r) return "";
    return "("+s.substr(l,r-l+1)+")";
}


void priorGet()
{
    int x = 0;
    for(int i = 5; i<s.size()-5; i++)
    {
        prior[i] = 1e9;
        if(s[i] == '+' || s[i] == '-')  //+-
        {
            prior[i] = x;
        }
        if(s[i] == '*' && s[i+1] == '*')   //**
        {
            prior[i] = x+3;
        }
        else
        if(s[i] == '*' && s[i-1] != '*')
        {
            prior[i] = x+1;
        }
        if(s[i] == '/')
        {
            prior[i] = x+2;
        }
        if(s[i] == ')')
        {
            x-=4;
        }
        if(s[i] == '(' && s[i-1] != 'n' && s[i-1] != 's' && s[i-1]!= 'g')
        {
            x+=4;
            prior[i] = x;
        }

        if((s[i] == 's' || s[i] == 'c' || s[i] == 'l' || s[i] == 't' || s[i] == 'c' || s[i] == 'a') && s[i-1] != 'c' && s[i-1] != 'o' && s[i-1]!='r' )
        {
            x += 4;
            prior[i] = x;
        }


    }

}



string prois(int l,int r)
{
    if(l>r) return "";
    if(Trivial(l,r) )
    {

        if(s[l] == 'x') return "1";
        else return "0";
    }
    int MinPrior = l;
    for(int i = r; i>=l; i--)
    {
        if( prior[i]<prior[MinPrior]) MinPrior = i;
        else
        if(prior[i] == prior[MinPrior] && s[MinPrior] =='*' && s[MinPrior+1] == '*' ) MinPrior = i;


     }
    return "(" + Factar(l,r,MinPrior) + ")";
}

string Factar(int l,int r, int Pr)
{
    if(s[Pr] == '+' || s[Pr] == '-')
    {
         return prois(l,Pr-1) + s[Pr] + prois(Pr+1,r);
    }

    if(s[Pr] == '/') //  /
    {
        return "(" + prois(l,Pr-1) + "*" + cops(Pr+1,r) + "-" + cops(l,Pr-1) + "*" + prois(Pr+1,r) + ")/(" + cops(Pr+1,r) + "**2)";
    }

    if(s[Pr] == '*' && s[Pr+1] == '*') // **
    {
        return Multiply(cops(l,r),"(" + Multiply(prois(Pr+2,r) , "ln" + cops(l,Pr-1)) + "+" + Multiply(cops(Pr+2,r) ,"1/" + cops(l,Pr-1) , prois(l,Pr-1)) + ")");
    }
    else
    if(s[Pr] == '*' && s[Pr-1] != '*') // *
    {
        return prois(l,Pr-1) + "*" + cop(Pr+1,r) + "+" + cops(l,Pr-1) + "*" + prois(Pr+1,r);
    }

    if(s[Pr] == '(') // ()
    {
        return prois(l+1,r-1);
    }
    if(s[Pr] == 'l') // ln
    {
        return "1/" + cop(Pr+2,r) + "*" + prois(Pr+3,r-1);
    }
    if(s[Pr] == 's') // sin
    {
        return "cos" + cop(Pr+3,r) + "*" +prois(Pr+4,r-1);
    }
    if(s[Pr] == 'c' && s[Pr+1] == 'o') // cos
    {
        return "-sin" + cop(Pr+3,r) + "*" +prois(Pr+4,r-1);
    }
    if(s[Pr] == 't') // tg
    {
        return "1/(cos" + cop(Pr+2,r) + ")**2" + "*" +prois(Pr+3,r-1);
    }
    if(s[Pr] == 'c' && s[Pr+1] == 't') // ctg
    {
        return "-1/(sin" + cop(Pr+3,r) + ")**2" + "*" +prois(Pr+4,r-1);
    }
    if(s[Pr] == 'a' && s[Pr+3] =='s') //arcsin
    {
        return "1/(1-" + cop(Pr+6,r) + "**2)**0.5" + "*" +prois(Pr+7,r-1);
    }
    if(s[Pr] == 'a' && s[Pr+3] =='t') //arctg
    {
        return "1/(1+" + cop(Pr+5,r) + "**2)" + "*" +prois(Pr+6,r-1);
    }
    if(s[Pr] == 'a' && s[Pr+3]=='c' && s[Pr+4] == 'o') //arccos
    {
        return "-1/(1-" + cop(Pr+6,r) + "**2)**0.5" + "*" +prois(Pr+7,r-1);
    }
    if(s[Pr] == 'a' && s[Pr+3] == 'c' && s[Pr+4] == 't') //arcctg
    {
        return "-1/(1+" + cop(Pr+6,r) + "**2)" + "*" +prois(Pr+7,r-1);
    }

}

bool Trivial(int l , int r)
{
    if(l == r)
        return true;
    for(int i = l; i<=r; i++)
        if(s[i] < '0' || s[i] > '9' )
            if(s[i] != '.' && s[i] != 'e' ) return false;

    return true;
}


bool ConstDetect(int l,int r)
{
    for(int i = l; i<=r; i++)
        if(s[i] == 'x') return false;

    return true;
}


string Multiply(string s1,string s2)
{
    if(s1 == "0" || s1 == "(0)" || s2 == "0" || s2 == "(0)" ) return "0";

    return s1 + "*" + s2;
}
string Multiply(string s1,string s2,string s3)
{
    return Multiply(Multiply(s1,s2),s3);
}


int main()
{
    freopen("deriv.in","r",stdin);
    freopen("deriv.out","w",stdout);
    string t;
    while(!cin.eof())
    {

        getline(cin,t);
        s.clear();
        for(int i = 0; i<t.size(); i++)
            if(t[i] != ' ') s.push_back(t[i]);

        s = "     " + s + "     ";
        prior.assign(s.size(),0);

        priorGet();

        cout<<prois(5,s.size()-6)<<"\n";

    }
    return 0;
}
