#include <iostream>
#include <cmath>
#include <exception>
#include <string>
#include <vector>

using namespace std;

class Locatie {
    string nume;
    float latitudine;
    float longitudine;
    double lat1, lat2;
    double long1, long2;
    double distanta_lat,distanta_long;
    double calcul1,calcul2;
    string name;
    double distanta;

public:

    Locatie() : latitudine(0), longitudine(0), lat1(0), lat2(0), long1(0), long2(0), distanta_lat(0), distanta_long(0), distanta(0), calcul1(0), calcul2(0) {}

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

    string getNume() {
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

    string tip;
    int nr_victime;
    int nivel_dez;

protected:
    int nivel_pericol;

public:

    Dezastru() : nr_victime(0), nivel_dez(0), nivel_pericol(0) {}

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

protected:

    int Calcul_nivel() { // calculez nivelul de pericol al dezastrului pe baza numarului de victime si a nivelului de dezastru
        if (nr_victime >= 100) {
            nivel_pericol += 4;
        } else if (nr_victime >= 50) {
            nivel_pericol += 3;
        } else if (nr_victime >= 20) {
            nivel_pericol += 2;
        } else nivel_pericol += 1;

        if (nivel_dez >= 100) {
            nivel_pericol += 4;
        } else if (nivel_dez >= 50) {
            nivel_pericol += 3;
        } else if (nivel_dez >= 25) {
            nivel_pericol += 2;
        } else nivel_pericol += 1;
    }

    friend istream& operator >> (istream &in, Dezastru &info) { // citesc informatiile despre dezastru
        cout << "Numarul victimelor: ";
        in >> info.nr_victime;
        cout << "Va rog alegeti nivelul dezastrului pe o scala de la 1 la 100: ";
        in >> info.nivel_dez;
        cout << "................................................................."<<endl;

        return in;
    }

public:

    int Nivel_pericol() const { // calculez nivelul de pericol al dezastrului pe baza nivelului de pericol

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


class Cutremur : public Dezastru {

    int magnitudine;
    bool tsunami;

public:

    Cutremur() : Dezastru(), magnitudine(0), tsunami(false) {}

    Cutremur(const Cutremur& copie) : Dezastru(copie) {
        this->magnitudine = copie.magnitudine;
        this->tsunami = copie.tsunami;
    }

    friend istream& operator>>(istream& in, Cutremur& info);

    int Calcul_nivel() {
        Dezastru::Calcul_nivel(); // calculez nivelul de pericol al dezastrului prin apelarea functiei din clasa de baza

        if(magnitudine >= 8) {
            nivel_pericol += 5;
        }else if(magnitudine >= 6) {
            nivel_pericol += 4;
        }else if(magnitudine >= 4) {
            nivel_pericol += 3;
        }else if(magnitudine >= 2) {
            nivel_pericol += 2;
        }else {
            nivel_pericol += 1;
        }

        if (tsunami) {
            nivel_pericol += 4;
        }

        return nivel_pericol;
    }

};

istream& operator>>(istream& in, Cutremur& info) {
    cout << "Intensitatea cutremurului (scala Richter): ";
    in >> info.magnitudine;
    cout << "A fost generat tsunami? (1 pentru da, 0 pentru nu): ";
    in >> info.tsunami;

    return in;
}

class Incendiu : public Dezastru {
private:
    bool gaze_naturale;
    bool substante_chimice;
    bool echipamente_electrice;

public:
    Incendiu() : Dezastru(), gaze_naturale(false), substante_chimice(false), echipamente_electrice(false) {}
    Incendiu(const Incendiu& incendiu) : Dezastru(incendiu), gaze_naturale(incendiu.gaze_naturale), substante_chimice(incendiu.substante_chimice), echipamente_electrice(incendiu.echipamente_electrice) {}

    friend istream& operator >> (istream& in, Incendiu& incendiu);

    int Calcul_nivel() {
        Dezastru::Calcul_nivel();

        if (gaze_naturale) {
            nivel_pericol += 2;
        }
        if (substante_chimice) {
            nivel_pericol += 3;
        }
        if (echipamente_electrice) {
            nivel_pericol += 1;
        }

        return nivel_pericol;
    }
};

istream& operator >> (istream& in, Incendiu& incendiu) {
    cout << "Existenta gazelor naturale (0 - nu, 1 - da): ";
    in >> incendiu.gaze_naturale;
    cout << "Existenta substantelor chimice (0 - nu, 1 - da): ";
    in >> incendiu.substante_chimice;
    cout << "Existenta echipamentelor electrice (0 - nu, 1 - da): ";
    in >> incendiu.echipamente_electrice;

    return in;
}

class Interventie {

protected:
    string echipa;
    string persoana_contact;
    int nr_persoane;
    bool disponibilitate;

public:
    Interventie(const string& echipa, const string& persoana_contact, int nr_persoane, bool disponibilitate)
            : echipa(echipa), persoana_contact(persoana_contact), nr_persoane(nr_persoane), disponibilitate(disponibilitate) {}

    Interventie () {
        echipa = "";
        persoana_contact = "";
        nr_persoane = 0;
        disponibilitate = false;
    }
    void Verificare_disponibilitate() {
        if (disponibilitate) {
            cout << echipa << " este disponibila" << endl;
            cout << "Persoana de contact este " << persoana_contact << endl;
            cout << "Numarul de persoane disponibile este " << nr_persoane << endl;
        } else {
            cout << echipa << " nu este disponibila" << endl;
        }
        cout<<"................................................................."<<endl;
    }
};

class Pompieri : public Interventie {

private:
    int capacitate_pompieri;
    bool autospeciala;

public:
    Pompieri(const string& echipa, const string& persoana_contact, int nr_persoane, bool disponibilitate, int capacitate_pompieri, bool autospeciala)
            : Interventie(echipa, persoana_contact, nr_persoane, disponibilitate), capacitate_pompieri(capacitate_pompieri), autospeciala(autospeciala) {}

    Pompieri() {
        echipa = "";
        capacitate_pompieri = 0;
        autospeciala = false;
    }

    void Verificare_disponibilitate() {
        if (disponibilitate) {
            cout << echipa << " este disponibila pentru interventii la incendiu" << endl;
            cout << "Persoana de contact este " << persoana_contact << endl;
            cout << "Numarul de pompieri disponibili este " << capacitate_pompieri << endl;
            if (autospeciala) {
                cout << "Echipa dispune de o autospeciala pentru interventii la incendiu" << endl;
            } else {
                cout << "Echipa nu dispune de o autospeciala pentru interventii la incendiu" << endl;
            }
        } else {
            cout << echipa << " nu este disponibila pentru interventii la incendiu" << endl;
        }
        cout<<"................................................................."<<endl;
    }
};

class Situatie {
public:
    virtual void Afectata(int damage) = 0;
    virtual bool Distrusa() const { return false; }
    virtual ~Situatie() {}
};

class Cladire : public Situatie {

protected:
    int viata;

public:
    Cladire(int viata) : viata(viata) {}

    Cladire() {
        viata = 100;
    }

    void Afectata(int damage) { //polimorfism - functia este suprascrisa
        viata = viata - damage;
    }

    bool Distrusa() const {
        return viata<= 0;
    }

    void verificare() const {
        if (Distrusa()) {
           cout << "Cladirea a fost distrusa!" << endl;
        }
        else {
            cout << "Cladirea este inca in picioare!" << endl;
        }
    }

};

class CladireNesigura : public exception {
private:
    string mesaj;
public:
    CladireNesigura(const string& mesaj) : mesaj(mesaj) {}

    const char* what() const throw() {
        return mesaj.c_str();
    }
};

class CladireSigura : public Cladire {
private:
    string stare;
public:
    CladireSigura(int viata): Cladire(viata), stare("sigura") {}

    void Afectata(int damage) {
        Cladire::Afectata(damage);
        if (viata <= 0) {
            stare = "nesigura";
            throw CladireNesigura("Cladirea este nesigura!");
        }
    }
    const string& get_stare() const {
        return stare;
    }
};

class Inundatie_exception : public exception {
private:
    string mesaj;
public:
    Inundatie_exception(const string& mesaj) : mesaj(mesaj) {}

    const char* what() const throw() override {
        return mesaj.c_str();
    }
};

class InundatieMonitorizare {
private:
    int nivel_apa;
public:
    InundatieMonitorizare(int nivel_apa) : nivel_apa(nivel_apa) {}

    InundatieMonitorizare() {
        nivel_apa = 0;
    }

    void Verificare_nivel_apa() {
        nivel_apa += 20;
        try {
            if (nivel_apa > 100) {
                throw Inundatie_exception("Nivelul apei este prea mare!");
            } else {
                cout << "Nivelul apei este normal!" << endl;
            }
        }
        catch (Inundatie_exception &e) {
            cerr << "Eroare: " << e.what() << endl;
            throw runtime_error("A aparut o problema in monitorizarea nivelului apei!");
        }
        catch (const exception &e) {
            cerr << "Eroare: " << e.what() << endl;
            throw runtime_error("Va rugam reincercati!");
        }
    }

};

class Total_Dezastre {
private:
    string nume;
    int nivel_pericol;
    int total;
    int dezastre;
    static vector<Total_Dezastre*> total_dezastre;
public:
    Total_Dezastre(string nume, int nivel_pericol) : nume(nume), nivel_pericol(nivel_pericol) {
        total_dezastre.push_back(this);
    }

    static int get_total_dezastre() {
        int total = 0;
        for (const auto& dezastre : total_dezastre) {
            total += dezastre->nivel_pericol;
        }
        return total;
    }

    static void Afisare() {
        cout << "Dezastrele inregistrate sunt: "<< endl;
        for (const auto& dezastre : total_dezastre) {
            cout <<" - "<< dezastre->nume << " cu nivelul de pericol " << dezastre->nivel_pericol << endl;
        }
    }
};

vector<Total_Dezastre*> Total_Dezastre::total_dezastre;

int main() {
    Locatie locatie1;
    Locatie locatie2;

    cin >> locatie1;
    cin >> locatie2;

    float distance = locatie1.Distanta_calculata(locatie2);
    cout<<locatie1<<endl;


    Dezastru dezastru1;
    cin>>dezastru1;

    Cutremur cutremur;
    cout<<"Introduceti datele pentru cutremur: "<<endl;
    cin>>cutremur;
    cutremur.Calcul_nivel();
    cutremur.Nivel_pericol();

    Incendiu incendiu;
    cout<<"Introduceti datele pentru incendiu: "<<endl;
    cin>>incendiu;
    incendiu.Calcul_nivel();
    incendiu.Nivel_pericol();

    Interventie interventie1("Echipa1", "Popescu Ion", 10, true);
    interventie1.Verificare_disponibilitate();

    Pompieri pompieri1("Echipa 1", "Ion Popescu", 5, true, 10, true);
    Pompieri pompieri2("Echipa 2", "Maria Ionescu", 7, false, 15, false);

    cout << "Detalii despre interventiile la incendiu:" << endl;
    pompieri1.Verificare_disponibilitate();
    cout << endl;
    pompieri2.Verificare_disponibilitate();

    Situatie* ptrCladire = new Cladire(100); //upcasting - pointerul de tip Situatie pointeaza catre un obiect de tip Cladire
    auto* ptrCladire1 = dynamic_cast<Cladire*>(ptrCladire);
    if(ptrCladire1){
        ptrCladire1->verificare(); // polimorfism - se apeleaza metoda din clasa Cladire (clasa derivata) si nu din clasa Situatie (clasa de baza)
    }
    delete ptrCladire;

    Situatie* ptrCladire_Sigura = new CladireSigura(100); //upcasting - pointerul de tip Situatie pointează către un obiect de tip Cladire_Rezidentiala
    auto* ptrCladire_Sigura1 = dynamic_cast<CladireSigura*>(ptrCladire_Sigura);
    if (ptrCladire_Sigura1) {
        try {
            ptrCladire_Sigura1->Afectata(50);
            cout << "Starea curenta: " << ptrCladire_Sigura1->get_stare() << endl;
            ptrCladire1->Afectata(60);
            cout << "Starea curenta: " << ptrCladire_Sigura1->get_stare() << endl;
        }
        catch (const exception& e) {
            cerr << "A aparut o exceptie: " << e.what() << endl;
        }
    }
    delete ptrCladire_Sigura;

    cout<<"------------------------------------------"<<endl;

    try {
        InundatieMonitorizare nivel(60);
        nivel.Verificare_nivel_apa();
        InundatieMonitorizare nivel2;
        nivel2.Verificare_nivel_apa();
    } catch (const exception& e) {
        cerr << "Eroare: " << e.what() << endl;
        return 1;
    }

    cout<<"------------------------------------------"<<endl;

    Total_Dezastre dezastre1("Cutremur", 10);
    Total_Dezastre dezastre2("Incendiu", 20);
    Total_Dezastre dezastre3("Inundatie", 30);

    cout<<"Nivelul total de pericol este: "<<Total_Dezastre::get_total_dezastre()<<endl;
    Total_Dezastre::Afisare();

    return 0;
}
