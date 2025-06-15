#include <TinyGPS++.h>  // Inclure la bibliothèque TinyGPS++

// Créer une instance TinyGPS++
TinyGPSPlus gps;  // Déclaration de l'objet gps

// Utiliser Serial1 pour communiquer avec le GPS (TX1 = 18, RX1 = 19 sur Arduino Due)
#define GPSserial Serial1  // Définir GPSserial comme alias pour Serial1

void setup() {
  // Initialiser les ports série
  Serial.begin(9600);         // Communication avec le PC
  GPSserial.begin(9600);      // Communication avec le module GPS

  Serial.println("Attendez que les données GPS soient reçues...");
  Serial.println("Lat: 33.246661, Long: -8.499092");
}

void loop() {
  // Lire les données GPS et les transmettre à l'analyseur TinyGPS++
  while (GPSserial.available() > 0) {
    char c = GPSserial.read();  // Lire un caractère depuis le GPS
    gps.encode(c);  // Traiter le caractère dans le parseur TinyGPS++

    // Si de nouvelles données de localisation sont disponibles
    if (gps.location.isUpdated()) {
      Serial.println("=== Localisation mise à jour ===");
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);  // Afficher la latitude
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);  // Afficher la longitude
      Serial.print("Altitude: ");
      Serial.println(gps.altitude.meters());  // Afficher l'altitude
      Serial.print("Nombre de satellites: ");
      Serial.println(gps.satellites.value());  // Afficher le nombre de satellites
      Serial.print("Précision HDOP: ");
      Serial.println(gps.hdop.value());  // Afficher la précision HDOP
      Serial.println("===============================");
    }
  }
}


