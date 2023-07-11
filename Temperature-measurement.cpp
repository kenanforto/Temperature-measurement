//TP 2018/2019: Tutorijal 14, Zadatak 1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

struct Temperatura
{
    int dan,mjesec,godina;
    std::string ime;
    std::vector<int> temp;
};

int main ()
{
    std::vector<Temperatura> t;
    std::ifstream ulaz("TEMPERATURE.TXT");
    if(!ulaz)
    std::cout<<"Datoteka TMPERATURE.TXT ne postoji!"<<std::endl;
    std::string ulazni;
    while(std::getline(ulaz,ulazni))
    {
        Temperatura el;
        auto p=ulazni.begin();
        int j=0;
        while(p!=ulazni.end())
        {
            int i=0;
            int broj=0;
            while(p!=ulazni.end() && (*p)!='/')
            {
                broj*=10;
                broj+=(*p)-'0';
                i++;
                p++;
            }
            if(j==0) el.dan=broj;
            else if(j==1) el.mjesec=broj;
            else el.godina=broj;
            j++;
            if(p!=ulazni.end())
            p++;
        }
        std::getline(ulaz,el.ime);
        std::getline(ulaz,ulazni);
        p=ulazni.begin();
        while(p!=ulazni.end())
        {
            int i=0;
            int broj=0;
           if(p!=ulazni.end() && *p!=',' && *p!='-')
           {
               int minus=0;
               if(p!=ulazni.begin())
               {
                   if((*(p-1))=='-')
                   minus=1;
               }

                while(p!=ulazni.end() && *p!=',' && *p!='-')
                {
                    
                    broj*=10;
                    broj+=(*p)-'0';
                    i++;
                    p++;
                }
               if(minus)
               {
               broj=broj*(-1);
               minus=false;
               }
                el.temp.push_back(broj);
           }
            if(p!=ulazni.end())
            p++;
        }

        t.push_back(el);
    }
    std::sort(t.begin(),t.end(),[](Temperatura t1,Temperatura t2)
    {
       if(t1.godina<t2.godina)
       return true;
       else if(t1.godina>t2.godina) return false;
       if(t1.mjesec<t2.mjesec)
       return true;
       else if(t1.mjesec>t2.mjesec)
       return false;
       if(t1.dan<t2.dan)
       return true;
       else if(t1.dan>t2.dan)
       return false;
       double prosjek1=0,prosjek2=0;
       int vel1=0,vel2=0;
       auto l=t1.temp.begin();
       while(l!=t1.temp.end())
       {
           prosjek1+=(*l);
           vel1++;
           l++;
       }
       l=t2.temp.begin();
       while(l!=t2.temp.end())
       {
           prosjek2+=(*l);
           vel2++;
           l++;
       }
       prosjek1=prosjek1/vel1;
       prosjek2=prosjek2/vel2;
       return prosjek1<prosjek2;
    });
    ulaz.close();
    std::ofstream ulaz1("IZVJESTAJ.TXT");
    auto o=t.begin();
    while(o!=t.end())
    {
        ulaz1<<(*o).ime<<std::endl;
        for(int i=0;i<(*o).ime.size();i++)
        {
            ulaz1<<"-";
        }
        ulaz1<<std::endl;
        ulaz1<<"Datum mjerenja: "<<(*o).dan<<"/"<<(*o).mjesec<<"/"<<(*o).godina<<std::endl;
        ulaz1<<"Minimalna temperatura: "<<*std::min_element((*o).temp.begin(),(*o).temp.end())<<std::endl;
        ulaz1<<"Maksimalna temperatura: "<<*std::max_element((*o).temp.begin(),(*o).temp.end())<<std::endl;
        double prosjek=0;
        auto i=(*o).temp.begin();
        int vel=0;
        while(i!=(*o).temp.end())
        {
            prosjek+=(*i);
            vel++;
            i++;
        }
        prosjek=prosjek/vel;
        ulaz1<<"Prosjecna temperatura: "<<std::fixed<<std::setprecision(2)<<prosjek<<std::endl;
        o++;
        ulaz1<<std::endl;
    }
	return 0;
}
