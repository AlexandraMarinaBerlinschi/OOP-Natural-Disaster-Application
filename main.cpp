#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class String{
    int size;
    char* sir;

public:
    friend class Locatie;
    friend class Dezastru;
    friend class Interventie;

    String ()
    {
        size = 0;
        sir = nullptr;
    }
    String(const char* s)
    {
        size = strlen(s);
        sir = new char[size+1];
        strcpy(sir, s);
        sir[size] = '\0';

    }

    String(const String& s)
    {
        this->size = s.size;
        this->sir = new char[size+1];
        strcpy(sir, s.sir);
    }

    String& operator=(const String& a)
    {
        if ( this != &a ) {
            delete[] sir;

            size = a.size;
            sir = new char[size+1];
            strcpy(sir, a.sir);
            sir[size] = '\0';
        }

        return *this;
    }

    char* get_sir()
    {
        return sir;
    }

    ~String()
    {
        if (sir != nullptr)
            delete[] sir;
    }

    friend ostream& operator << (ostream& out, const String& s){
        out << s.sir;
        return out;
    }

    friend istream& operator>>(istream& in, String& s) {
        string temp;
        in >> temp;
        s.size = temp.length();
        s.sir = new char[s.size + 1];
        strcpy(s.sir, temp.c_str());
        return in;
    }

};

class Locatie {
    String nume;
    float latitudine;
    float longitudine;
    double lat1, lat2;
    double long1, long2;
    double distanta_lat,distanta_long;
    double distanta;
    double calcul1,calcul2;
    String name;
public:

    friend class String;

    Locatie() : name(""), latitudine(0), longitudine(0), lat1(0), lat2(0), long1(0), long2(0), distanta_lat(0), distanta_long(0), distanta(0), calcul1(0), calcul2(0) {}

    Locatie(const Locatie& copie) {
        latitudine=copie.latitudine;
        longitudine=copie.longitudine;
        nume=copie.nume;
        lat1=copie.lat1;
        lat2=copie.lat2;
        long1=copie.long1;
        long2=copie.long2;
        distanta_lat=copie.distanta_lat;
        distanta_long=copie.distanta_long;
        distanta=copie.distanta;
        calcul1=copie.calcul1;
        calcul2=copie.calcul2;
        name=copie.name;
    }

    String getNume() {
        return nume;
    }
    float getLatitudine() const {
        return latitudine;
    }
    float getLongitudine() const {
        return longitudine;
    }

    friend istream& operator >> (istream& in, Locatie& loc);
    friend ostream& operator << (ostream& out, const Locatie& loc);

    float Distanta_calculata(Locatie& copie)  { // calculez distanta dintre 2 locatii - transform latitudinea si longitudinea in radiani si apoi calculez distanta dintre ele
        name= copie.getNume();
        lat1=latitudine * 3.14159265359/180.0;
        long1=longitudine * 3.14159265359/180.0;
        lat2=copie.getLatitudine()*3.14159265359/180;
        long2=copie.getLongitudine() * 3.14159265359/180;
        distanta_lat=lat2-lat1;
        distanta_long=long2-long1;
        calcul1=sin(distanta_lat/2)*sin(distanta_lat/2)+cos(lat1)*cos(lat2)*sin(distanta_long/2)*sin(distanta_long/2);
        calcul2=2*atan2(sqrt(calcul1), sqrt(1-calcul1));
        distanta=6371.0*calcul2;

        return distanta;
    }

};

    istream& operator >> (istream& in, Locatie& loc) { // citesc locatia prin coordonate astfel incat sa o transform in km
    cout << "Numele locatiei: ";
    in >> loc.nume;
    cout << "Latitudinea locatiei: ";
    in >> loc.latitudine;
    cout << "Longitudinea locatiei: ";
    in >> loc.longitudine;
    return in;
    }

    ostream& operator << (ostream& out, const Locatie& loc) { // afisez locatia
        out<<"Distanta dintre "<<loc.nume<<" si "<<loc.name<<" este de "<<loc.distanta<<" km "<<endl;
        out<<"--------------------------------------------------------------------"<<endl;
        return out;
    }

class Dezastru {
    private:
    String tip;
    int nr_victime;
    int nivel_dez;
    int nivel_pericol;

public:

     friend class String;

    Dezastru() : tip(""), nr_victime(0), nivel_dez(0), nivel_pericol(0) {}

    Dezastru(const Dezastru& copie) {
        this->tip=copie.tip;
        this->nr_victime=copie.nr_victime;
        this->nivel_dez=copie.nivel_dez;
        this->nivel_pericol=copie.nivel_pericol;
    }

    Dezastru& operator=(const Dezastru& copie) {
        if (this != &copie) {
            tip = copie.tip;
            nr_victime = copie.nr_victime;
            nivel_dez = copie.nivel_dez;
            nivel_pericol = copie.nivel_pericol;
        }
        return *this;
    }

    friend istream& operator >> (istream& in, Dezastru& info);

    int Calcul_nivel() { // calculez nivelul de pericol al dezastrului pe baza numarului de victime si a nivelului de dezastru
        if (nr_victime>=100) {
            nivel_pericol += 4;
        }else if (nr_victime>=50) {
            nivel_pericol += 3;
        }else if (nr_victime>=20) {
            nivel_pericol += 2;
        }else nivel_pericol += 1;

        if(nivel_dez>=100) {
            nivel_pericol += 4;
        }else if (nivel_dez>=50) {
            nivel_pericol += 3;
        }else if (nivel_dez>=25) {
            nivel_pericol += 2;
        }else nivel_pericol += 1;


        if ( nivel_pericol >= 7) { // afisez nivelul de pericol al dezastrului
            cout<<"Nivel ridicat de pericol"<<endl;
            cout<<"--------------------------------------------------------------------"<<endl;
        }else if(nivel_pericol >= 4) {
            cout<<"Nivel mediu de pericol"<<endl;
            cout<<"--------------------------------------------------------------------"<<endl;
        }else if(nivel_pericol >= 1) {
            cout<<"Nivel scazut de pericol"<<endl;
            cout<<"--------------------------------------------------------------------"<<endl;
        }
        return nivel_pericol;
    }
};
    istream& operator >> (istream &in, Dezastru &info) { // citesc informatiile despre dezastru
        cout << "Numarul victimelor: ";
        in >> info.nr_victime;
        cout << "Va rog alegeti nivelul dezastrului pe o scala de la 1 la 100: ";
        in >> info.nivel_dez;

        return in;
    }

class Interventie {

    private:
        String echipa;
        String persoana_contact;
        int nr_persoane;
        bool disponibilitate;
    public:

        friend class String;

        Interventie() : echipa(""), persoana_contact(""), nr_persoane(0), disponibilitate(false) {}

        Interventie(const Interventie& copie) {
            this->echipa=copie.echipa;
            this->persoana_contact=copie.persoana_contact;
            this->nr_persoane=copie.nr_persoane;
            this->disponibilitate=copie.disponibilitate;
        }

        Interventie& operator=(const Interventie& copie) {
            if (this != &copie) {
                echipa = copie.echipa;
                persoana_contact = copie.persoana_contact;
                nr_persoane = copie.nr_persoane;
                disponibilitate = copie.disponibilitate;
            }
            return *this;
        }


    void setEchipa(const String& echipa) { // setez datele despre echipa de interventie
        this->echipa = echipa;
    }

    void setPersoanaContact(const String& persoana_contact) {
        this->persoana_contact = persoana_contact;
    }

    void setNrPersoane(int nr_persoane) {
        this->nr_persoane = nr_persoane;
    }

    void setDisponibilitate(bool disponibilitate) {
        this->disponibilitate = disponibilitate;
    }


        void Verificare_disponibilitate() { // verific daca echipa de interventie este disponibila
            if (disponibilitate) { // daca echipa de interventie este disponibila, afisez datele despre aceasta
                cout<<echipa<<" este disponibila"<<endl;
                cout<<"Persoana de contact este "<<persoana_contact<<endl;
                cout<<"Numarul de persoane disponibile este "<<nr_persoane<<endl;
            }else cout<<echipa<<" nu este disponibila"<<endl;
        }
};

int main() {
    Locatie locatie1;
    Locatie locatie2;

    cin >> locatie1;
    cin >> locatie2;

    float distance = locatie1.Distanta_calculata(locatie2);
    cout<<locatie1<<endl;

    Dezastru dezastru1;

    cin>>dezastru1;

    int nivel = dezastru1.Calcul_nivel();

    // ofer date despre echipa de interventie si verific daca aceasta este disponibila
    Interventie interventie1;
    interventie1.setEchipa("Echipa 1");
    interventie1.setPersoanaContact("Andreea Pop");
    interventie1.setNrPersoane(10);
    interventie1.setDisponibilitate(true);

    Interventie interventie2;
    interventie2.setEchipa("Echipa 2");
    interventie2.setPersoanaContact("Ion Marin");
    interventie2.setNrPersoane(5);
    interventie2.setDisponibilitate(false);

    interventie1.Verificare_disponibilitate();
    interventie2.Verificare_disponibilitate();

    return 0;
}
