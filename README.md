# OS_1
Fully functional operating system kernel / C++

Cilj ovog projekta jeste realizacija malog, ali sasvim funkcionalnog jezgra (engl. kernel)
operativnog sistema koji podržava niti (engl. multithreaded operating system) sa deljenjem
vremena (engl. time sharing). U daljem tekstu, ovakav sistem biće kratko nazivan samo jezgrom.
U okviru ovog projekta, realizovaće se jedan podsistem ovog jezgra – podsistem za upravljanje nitima. 
Ovaj podsistem treba da obezbedi koncept niti (engl. thread), kao i usluge
kreiranja i pokretanja niti, zatim koncept semafora i događaja vezanog za prekid, i podršku
deljenju vremena (engl. time sharing). Jezgro treba da bude realizovano tako da korisnički program (aplikacija) 
i samo jezgro dele isti adresni prostor, odnosno da predstavljaju jedinstven program. Konkurentni
procesi kreirani unutar aplikacije biće zapravo samo "laki" procesi, tj. niti (engl. thread).
Aplikacija i jezgro treba da se prevode i povezuju u jedan isti program, tj. da se pišu kao
"jedinstven" izvorni kod. U cilju demonstracije i lakšeg razvoja, testiranja i eksperimentisanja, jezgro i
aplikacija treba da se izvršavaju na PC računaru, pod operativnim sistemom Windows (bilo
kojim 32-bitnim), kao konzolna aplikacija.


Zadatak 1: Podsistem za upravljanje nitima
Uvod
Cilj ovog zadatka jeste realizacija podsistema jezgra za upravljanje nitima (engl. thread).
Zahtevi u okviru ovog zadatka jesu realizacija:
- koncepta niti (engl. thread), uz operacije kreiranja i pokretanja niti;
- promene konteksta (engl. context switch) i preuzimanja (engl. preemption) i to na
sledeće načine:
- eksplicitnim zahtevom same niti (sinhrono, eksplicitno preuzimanje);
- zbog pojave prekida (asinhrono, implicitno preuzimanje);
- zbog isteka dodeljenog vremena (asinhrono, implicitno preuzimanje), kao
podrška deljenju vremena (engl. time sharing);
- koncepta standardnog semafora;
- koncepta događaja (zapravo binarnog semafora) na kome samo jedna nit može da čeka
blokirana, a koji se signalizira zadatim prekidom.

Koncept niti
Opis zadatka

Potrebno je obezbediti koncept niti. Sve niti pokrenute unutar aplikacije dele isti
adresni prostor (statičke i dinamičke podatke), ali poseduju sopstvene kontrolne stekove na
kojima se čuva trag ugnježdenih poziva funkcija, kao i automatski podaci tih funkcija.
Nit se kreira nad određenom funkcijom i kada se pokrene izvršavanje niti, novi tok
kontrole počinje od poziva te funkcije. Dalji tok niti zavisi od sadržaja te funkcije.
Potrebno je obezbediti sledeće operacije nad nitima:
- kreiranje niti: ova operacija samo kreira novu nit u jezgru nad određenom funkcijom,
ali ne pokreće njeno izvršavanje; u slučaju da je prosleđena vrednost parametra
timeSlice=0, kreirana niti ima neograničeni vremenski interval izvršavanja.
- pokretanje niti: ova operacija pokreće novi tok izvršavanja nad funkcijom nad kojom
je kreirana nit;
- eksplicitno preuzimanje (engl. dispatch);
- Identifikacioni broj: sistem treba da obezbedi da svaka nit prilikom kreiranja dobije jedinstveni
identifikacioni broj (ID). Sistem takodje treba da obezbedi dohvatanje niti
samo na osnovu identifikacionog broja, kao i dohvatanje identifikacionog broja (ID)
tekuće niti (running) i proizvoljne niti (posedovanjem pokazivača na objekat koji
predstavlja tu nit).
Rešenje treba da obezbedi mogućnost:
- kreiranja neograničenog broja korisničkih niti (gornja granica mogućeg broja
korisničkih niti može biti ograničena isključivo raspoloživom memorijom);
- alokacije prostora za kontrolni stek niti maksimalne veličine 64KB.



Promena konteksta i preuzimanje
Opis zadatka

Potrebno je realizovati promenu konteksta (engl. context switch) i preuzimanje u sledećim
situacijama:

1. Na eksplicitni zahtev niti (sinhrono preuzimanje) pozivom funkcije dispatch() koja
vrši eksplicitno preuzimanje.
2. Na pojavu prekida (asinhrono preuzimanje), ali samo uz korišćenje koncepta događaja
koji će biti opisan naknadno.
3. Zbog operacije na nekoj sinhronizacionoj primitivi, tj. na semaforu ili događaju, kako
je opisano kasnije (sinhrono preuzimanje).
4. Po isteku vremenskog intervala dodeljenog niti za izvršavanje (engl. time slice).
Vremenski interval koji se dodeljuje procesu pri svakom povratku konteksta zadaje se
prilikom kreiranja niti, kao parametar (umnožak od 55ms). Vrednost 0 ovog parametra
označava da vreme izvršavanja date niti nije ograničeno, već će se ona izvršavati
(kada dobije procesor) sve dok ne dođe do preuzimanja iz nekog drugog razloga.
5. Eksplicitnim pozivom operacije waitToComplete().



Koncept semafora
Opis zadatka

Potrebno je realizovati koncept standardnog brojačkog semafora sa operacijama wait i signal
sa vremenski ograničenim intervalom čekanja. Ukoliko je vrednost semafora negativna, tada
na semaforu mora biti onoliko blokiranih niti koliko je apsolutna vrednost semafora.
Operacija wait se razlikuje od uobičajene po tome što prihvata i vraća po jedan ceo broj (int).
Prihvaćeni ceo broj označava maksimalno trajanje blokiranosti pozivajuće niti (umnožak od
55ms). Zadata vrednost 0 znači da dužina čekanja nije vremenski ograničena. Ukoliko je nit
deblokirana zbog isteka vremena, rezultat operacije wait je vrednost 0, dok je u ostalim
slučajevima vrednost 1.



Koncept događaja
Opis zadatka

Potrebno je realizovati koncept događaja, koji predstavlja binarni semafor na kome
može biti blokirana nit, a koji se signalizira prekidom. Drugim rečima, koncept događaja
omogućava da se neka nit blokira čekajući na prekid. Na ovaj način može se realizovati
koncept sporadičnog procesa (niti), tj. procesa koji se aktivira na pojavu spoljašnjeg događaja
(predstavljenog prekidom), obavlja neku svoju aktivnost, a potom se ponovo blokira čekajući
na sledeću pojavu istog događaja. Ukoliko se prekid dešava periodično, onda se isti koncept
može iskoristiti za realizaciju periodičnog procesa (niti).
Pošto prekidna rutina ne može da bude nestatička metoda neke klase, za
implementaciju opisanog sistema događaja potrebno je implementirati klasu IVTEntry i makro
PREPAREENTRY. Klasa IVTEntry treba da enkapsulira sve podatke i operacije nad tim
podacima koji su potrebni za evidenciju događaja vezanog za neki prekid (tabela prekida ima
ukupno 256 ulaza). Ova klasa treba da obezbedi mogućnost dohvatanja pokazivača na objekat
IVTEntry koji je vezan za zadati ulaz, jer će jedini parametar konstruktora događaja biti redni
broj ulaza u IVT. Makro PREPAREENTRY treba da za korisnika generiše definicije svih
potrebnih podataka i funkcija za jedan ulaz u IVT. Makro treba da prihvata dva parametra:
prvi je broj ulaza za koji se generišu definicije i na osnovu kojeg makro svaki put generiše
drugačije nazive definisanih promenljivih i funkcija, a drugi logička vrednost koja govori da li
treba pozivati staru prekidnu rutinu (1 – treba, 0 – ne treba). Objekat i funkcija koje je
neophodno definisati su:

- objekat tipa IVTEntry u kojem će biti sačuvani svi potrebni podaci vezani za ulaz za
koji se definiše objekat;
- prekidna rutina koja svaki put kada je pozvana treba da pozove signal na događaju koji
je vezan za taj ulaz; sve potrebne informacije se čuvaju u objektu tipa IVTEntry.
Koncept događaja treba da omogući sledeće radnje:
- inicijalizaciju, zadavanjem broja ulaza u vektor tabeli (IVT) za čiji se prekid vezuje
dati događaj; pri inicijalizaciji treba obaviti sve potrebne radnje, između ostalog i
inicijalizaciju ili preusmeravanje starog vektora iz datog ulaza; smatrati da se nad
jednim ulazom u vektor tabeli može kreirati samo jedan objekat događaja.
- operaciju wait kojom se pozivajuća nit blokira; obezbediti da samo nit koja je kreirala
događaj može na njemu i da se blokira; poziv ove operacije iz niti koja nije vlasnik
događaja nema efekta;
- operaciju signal koja deblokira nit blokiranu na događaju i koju treba da pozove
prekidna rutina koja je vezana za prekid događaja, a koju obezbeđuje korisnik;
preciznije, korisnička prekidna rutina koja je vezana za isti ulaz u IVT za koji je vezan
i događaj, treba samo da pozove ovu operaciju signal događaja koji odgovara tom
prekidu.

Kada se dogodi prekid, treba uvek vršiti preuzimanje (naravno, pod uslovom da se
izvršavanje ove prekidne rutine nije ugnezdilo u izvršavanje nekog drugog dela sistemskog
koda), ali tako što će se deblokirana nit koja čeka na događaj najpre smestiti u red spremnih
(operacijom Scheduler::put()), a onda iz reda spremnih uzeti naredna nit za izvršavanje
(operacijom Scheduler::get()). To znači da se može dogoditi čak i da ista, prekinuta nit
nastavi sa izvršavanjem, ili da to bude neka druga nit od onih koje su aktivirane prekidom, što
zavisi isključivo od algoritma raspoređivanja koji je nepoznat i nedostupan delu jezgra koji
realizuje student, pošto je enkapsuliran (sakriven) iza interfejsa zadatog u zaglavlju
schedule.h.
