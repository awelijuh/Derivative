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
    for(int i = 0; i<s.size(); i++)
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
        return cops(l,r) + "*(" + prois(Pr+2,r) + "*ln" + cops(l,Pr-1) + "+" + cops(Pr+2,r) + "*1/" + cops(l,Pr-1) + "*" + prois(l,Pr-1) + ")";
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
    if(s[Pr] == 'a' && s[Pr+3] =='s')
    {
        return "1/(1-" + cop(Pr+6,r) + "**2)**0.5" + "*" +prois(Pr+7,r-1);
    }
    if(s[Pr] == 'a' && s[Pr+3] =='t')
    {
        return "1/(1+" + cop(Pr+5,r) + "**2)" + "*" +prois(Pr+6,r-1);
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


int main()
{
    freopen("deriv.in","r",stdin);
    freopen("deriv.out","w",stdout);

    char c;
    while(scanf("%c",&c) == 1 && c!='\n' )
    {
        if(c != ' ')
            s.push_back(c);
    }
    prior.assign(s.size()+5,0);
    priorGet();

    cout<<prois(0,s.size()-1);


    return 0;
}
