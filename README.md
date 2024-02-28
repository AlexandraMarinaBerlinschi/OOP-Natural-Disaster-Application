## Proiect POO 
## Aplicatie Dezastre naturale


Tema aleasa este prezentarea datelor unei aplicatii pentru dezastre naturale.
Clasele implementate sunt urmatoarele:

* Clasa Locatie:

Permite reprezentarea unei locații geografice, stocând numele, latitudinea și longitudinea.
Calculează distanța între două locații folosind formula Haversine.
Supraîncarcă operatorii de citire și afișare pentru a permite citirea și afișarea informațiilor despre locații.
* Clasa Dezastru:

Reprezintă un dezastru general, cu caracteristici precum tipul, numărul de victime și nivelul de dezastu.
Calculează nivelul de pericol al dezastrului pe baza numărului de victime și a nivelului de dezastru.
Implementează suprascrierea operatorilor de citire și afișare pentru interacțiunea cu utilizatorul.
* Clasa Cutremur:

Este o subclasă a clasei Dezastru și adaugă caracteristici specifice cutremurelor, cum ar fi magnitudinea și informații despre tsunami.
Calculează nivelul de pericol al unui cutremur, luând în considerare magnitudinea și existența unui tsunami.
Suprascrie operatorul de citire pentru a citi informații despre un cutremur.
* Clasa Incendiu:

Este o subclasă a clasei Dezastru și adaugă caracteristici specifice incendiilor, cum ar fi existența gazelor naturale, a substanțelor chimice și a echipamentelor electrice.
Calculează nivelul de pericol al unui incendiu, luând în considerare existența diferitelor tipuri de substanțe și echipamente.
Suprascrie operatorul de citire pentru a citi informații despre un incendiu.
* Clasa Interventie:

Reprezintă o intervenție generală în caz de dezastru, stocând informații despre echipă, persoana de contact și disponibilitate.
Verifică disponibilitatea echipei și afișează informațiile relevante.
* Clasa Pompieri:

Este o subclasă a clasei Interventie și adaugă caracteristici specifice intervențiilor cu pompieri, cum ar fi capacitatea și disponibilitatea autospecialei.
Verifică disponibilitatea echipei de pompieri și afișează informațiile relevante.
* Clasa Situatie și subclasele sale:

Reprezintă diverse situații care pot apărea în caz de dezastru, cum ar fi starea unei clădiri și nivelul apei în caz de inundație.
Permit monitorizarea și gestionarea stării acestor situații.
* Clasa Total_Dezastre:

Gestionează informații despre toate dezastrele înregistrate și permite afișarea lor.
* Clasa Manager:

Gestionează dezastrul curent și permite afișarea acestuia.
* Funcția main:

Este punctul de intrare în program și interacționează cu utilizatorul pentru a citi informații despre locații, dezastrue și intervenții, și pentru a afișa diverse informații și stări.
Realizează diverse simulări și verificări, inclusiv simularea afectării unei clădiri și verificarea unui număr de telefon.
Acest cod folosește concepte precum moștenirea, polimorfismul, gestionarea excepțiilor, șabloanele de design Factory și Singleton, precum și algoritmi de sortare și căutare.
