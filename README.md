# TP_GESTION_DES_VOLS_BILLETS_DAVION
-Analyse du projet

En analysant le projet de gestion des vols, ma conception est la suivante :
Le projet a pour objectif de faciliter l'achat de billets d'avion, afin que les passagers n'aient plus besoin de se déplacer à l'agence pour acheter un billet ou annuler leur réservation.
Il permettra aussi à l'agence de mieux gérer les vols, les réservations (y compris les réservations annulées) et les informations personnelles des passagers.
Enfin, il fera gagner du temps à l'agence dans la gestion des places disponibles et occupées, tout en lui permettant de savoir quels passagers occupent les places et lesquels ont annulé leur réservation.
- Les classes, leurs attributs et leurs méthodes
Classe Passagers
Attributs : numeroIdentification, nom, prenom, dateExpirationPasseport
Méthode : afficherInformation()
Classe Vol
Attributs : numeroVol, villeDepart, villeArrivee, dateHeureDepart, dateHeureArrivee, nombrePlaces
Méthodes : afficherInformations(), placesDisponibles(), annuler()
Classe Place
Attribut : numero
Méthodes : occupe(), disponible()
Classe Reservation
Attributs : id, typeReservation, placeReserve, dateHeureExpirationReservation
Méthodes : annule(), nonAnnule()
Classe Agence
Attributs : nomAgence, listePassagers, listeReservations, listePlaces, listeVols
Méthodes : ajouterPassagers(), ajouterReservation(), annulerReservation(), rembourserReservation()
- Les relations entre les classes
Un vol contient plusieurs places, et chaque place appartient à un seul vol.
Un vol reçoit plusieurs réservations, et chaque réservation concerne un seul vol.
Un passager peut avoir une réservation, et une réservation concerne un passager.
Un passager peut occuper plusieurs places, et une place peut être associée à plusieurs passagers.
L'agence gère les passagers, les vols, les places et les réservations.

Pour l’incrémentation en C++, j’ai fait le choix de prendre L’agence Air Benin et l'exemple de 2 passagers nommés Koffi et Marie
