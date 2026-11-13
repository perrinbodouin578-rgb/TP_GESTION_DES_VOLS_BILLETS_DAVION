#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ======================= Classe Passagers =======================
class Passagers {
private:
    int numeroIdentification;
    string nom;
    string prenom;
    string dateExpirationPasseport;

public:
    Passagers(int numero, const string& nom, const string& prenom,
              const string& dateExpiration)
        : numeroIdentification(numero), nom(nom), prenom(prenom),
          dateExpirationPasseport(dateExpiration) {}

    int getNumeroIdentification() const { return numeroIdentification; }

    void afficherInformation() const {
        cout << "Passager #" << numeroIdentification << " : " << prenom << " "
             << nom << " (passeport valable jusqu'au "
             << dateExpirationPasseport << ")" << endl;
    }
};

// ======================= Classe Place =======================
class Place {
private:
    int numero;
    bool estOccupee;

public:
    explicit Place(int numero) : numero(numero), estOccupee(false) {}

    int getNumero() const { return numero; }
    bool getEstOccupee() const { return estOccupee; }

    void occupe() { estOccupee = true; }
    void nonOccupe() { estOccupee = false; }
};

// ======================= Classe Reservation =======================
class Reservation {
private:
    int id;
    int placeReserve;
    string dateHeureExpirationReservation;
    string classe;
    int numeroPassager;   // association avec Passagers
    string numeroVol;     // association avec Vol
    bool estValidee;
    bool estAnnulee;
    bool estRembourseee;

public:
    Reservation(int id, int placeReserve, const string& dateHeureExpiration,
                const string& classe, int numeroPassager, const string& numeroVol)
        : id(id), placeReserve(placeReserve),
          dateHeureExpirationReservation(dateHeureExpiration), classe(classe),
          numeroPassager(numeroPassager), numeroVol(numeroVol),
          estValidee(false), estAnnulee(false), estRembourseee(false) {}

    int getId() const { return id; }
    int getPlaceReserve() const { return placeReserve; }
    int getNumeroPassager() const { return numeroPassager; }
    const string& getNumeroVol() const { return numeroVol; }
    bool getEstAnnulee() const { return estAnnulee; }
    bool getEstRembourseee() const { return estRembourseee; }

    void valide() { estValidee = true; }
    void annule() { estAnnulee = true; estValidee = false; }
    void marquerRembourseee() { estRembourseee = true; }

    void afficher() const {
        cout << "Reservation #" << id << " | vol " << numeroVol << " | place "
             << placeReserve << " | classe " << classe
             << " | expire le " << dateHeureExpirationReservation
             << " | passager #" << numeroPassager << " | statut : "
             << (estAnnulee ? "annulee" : (estValidee ? "validee" : "en attente"))
             << endl;
    }
};

// ======================= Classe Vol =======================
class Vol {
private:
    string numeroVol;
    string villeDepart;
    string villeArrivee;
    string dateHeureDepart;
    string dateHeureArrivee;
    int nombrePlaces;
    vector<Place> places;   // un vol contient 1..* places

public:
    Vol(const string& numeroVol, const string& depart, const string& arrivee,
        const string& dateDepart, const string& dateArrivee, int nombrePlaces)
        : numeroVol(numeroVol), villeDepart(depart), villeArrivee(arrivee),
          dateHeureDepart(dateDepart), dateHeureArrivee(dateArrivee),
          nombrePlaces(nombrePlaces) {
        for (int i = 1; i <= nombrePlaces; i++) {
            places.push_back(Place(i));
        }
    }

    const string& getNumeroVol() const { return numeroVol; }

    Place* trouverPlace(int numero) {
        for (size_t i = 0; i < places.size(); i++) {
            if (places[i].getNumero() == numero) return &places[i];
        }
        return nullptr;
    }

    int placesDisponibles() const {
        int libres = 0;
        for (size_t i = 0; i < places.size(); i++) {
            if (!places[i].getEstOccupee()) libres++;
        }
        return libres;
    }

    void afficherInformations() const {
        cout << "Vol " << numeroVol << " : " << villeDepart << " -> "
             << villeArrivee << " | depart " << dateHeureDepart
             << " | arrivee " << dateHeureArrivee << " | places libres : "
             << placesDisponibles() << "/" << nombrePlaces << endl;
    }

    void annuler() {
        cout << "Le vol " << numeroVol << " est annule." << endl;
    }
};

// ======================= Classe Agence =======================
class Agence {
private:
    string nomAgence;
    vector<Passagers> passagers;
    vector<Reservation> reservations;
    vector<Vol> vols;
    int prochainIdReservation;

    Vol* trouverVol(const string& numeroVol) {
        for (size_t i = 0; i < vols.size(); i++) {
            if (vols[i].getNumeroVol() == numeroVol) return &vols[i];
        }
        return nullptr;
    }

    bool passagerExiste(int numero) const {
        for (size_t i = 0; i < passagers.size(); i++) {
            if (passagers[i].getNumeroIdentification() == numero) return true;
        }
        return false;
    }

    Reservation* trouverReservation(int id) {
        for (size_t i = 0; i < reservations.size(); i++) {
            if (reservations[i].getId() == id) return &reservations[i];
        }
        return nullptr;
    }

public:
    explicit Agence(const string& nom) : nomAgence(nom), prochainIdReservation(1) {}

    void ajouterPassagers(const Passagers& p) { passagers.push_back(p); }

    void ajouterVol(const Vol& v) { vols.push_back(v); }

    // Cree une reservation et occupe la place
    int ajouterReservation(int numeroPassager, const string& numeroVol,
                           int numeroPlace, const string& classe,
                           const string& dateHeureExpiration) {
        if (!passagerExiste(numeroPassager)) {
            cout << "Erreur : passager inconnu." << endl;
            return -1;
        }
        Vol* vol = trouverVol(numeroVol);
        if (vol == nullptr) {
            cout << "Erreur : vol inconnu." << endl;
            return -1;
        }
        Place* place = vol->trouverPlace(numeroPlace);
        if (place == nullptr || place->getEstOccupee()) {
            cout << "Erreur : place inexistante ou deja occupee." << endl;
            return -1;
        }
        place->occupe();
        Reservation r(prochainIdReservation, numeroPlace, dateHeureExpiration,
                      classe, numeroPassager, numeroVol);
        r.valide();
        reservations.push_back(r);
        cout << "Reservation #" << prochainIdReservation << " enregistree." << endl;
        return prochainIdReservation++;
    }

    // Annule la reservation et libere la place
    void annulerReservation(int idReservation) {
        Reservation* r = trouverReservation(idReservation);
        if (r == nullptr || r->getEstAnnulee()) {
            cout << "Erreur : reservation introuvable ou deja annulee." << endl;
            return;
        }
        r->annule();
        Vol* vol = trouverVol(r->getNumeroVol());
        if (vol != nullptr) {
            Place* place = vol->trouverPlace(r->getPlaceReserve());
            if (place != nullptr) place->nonOccupe();
        }
        cout << "Reservation #" << idReservation << " annulee." << endl;
    }

    // Rembourse uniquement une reservation annulee
    void rembourserReservation(int idReservation) {
        Reservation* r = trouverReservation(idReservation);
        if (r == nullptr || !r->getEstAnnulee() || r->getEstRembourseee()) {
            cout << "Remboursement impossible pour la reservation #"
                 << idReservation << "." << endl;
            return;
        }
        r->marquerRembourseee();
        cout << "Reservation #" << idReservation << " remboursee." << endl;
    }

    void afficherEtat() const {
        cout << "\n===== Agence " << nomAgence << " =====" << endl;
        for (size_t i = 0; i < passagers.size(); i++) passagers[i].afficherInformation();
        for (size_t i = 0; i < vols.size(); i++) vols[i].afficherInformations();
        for (size_t i = 0; i < reservations.size(); i++) reservations[i].afficher();
    }
};

// ======================= Programme principal =======================
int main() {
    Agence agence("Air Benin Voyages");

    agence.ajouterPassagers(Passagers(1, "Dossou", "Koffi", "2030-05-12"));
    agence.ajouterPassagers(Passagers(2, "Adjovi", "Marie", "2029-09-30"));

    agence.ajouterVol(Vol("AF123", "Cotonou", "Paris",
                          "2026-12-20 14:00", "2026-12-20 21:30", 5));

    int r1 = agence.ajouterReservation(1, "AF123", 3, "Economique", "2026-12-15 18:00");
    int r2 = agence.ajouterReservation(2, "AF123", 3, "Affaires", "2026-12-15 18:00"); // place deja prise
    int r3 = agence.ajouterReservation(2, "AF123", 4, "Affaires", "2026-12-15 18:00");
    (void)r2;
    (void)r3;

    agence.afficherEtat();

    agence.annulerReservation(r1);
    agence.rembourserReservation(r1);

    agence.afficherEtat();
    return 0;
}
