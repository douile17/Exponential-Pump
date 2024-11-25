/*
 * Project: Exponential Pump
 * Author: Andrew ZICLER
 * Year: 2024
 *
 * Description:
 * This code controls a Watson Marlow pump based on an exponential function 
 * using an Industruino. It is designed to provide precise control in applications 
 * requiring dynamic flow adjustments.
 *
 * License:
 * This project is licensed under the MIT License. You are free to use, modify, 
 * and distribute it, as long as this original notice is retained.
 *
 * MIT License:
 * The software is provided "as is", without warranty of any kind, express or implied, 
 * including but not limited to the warranties of merchantability, fitness for a particular purpose, 
 * and non-infringement. In no event shall the authors or copyright holders be liable 
 * for any claim, damages, or other liability, whether in an action of contract, tort, or otherwise, 
 * arising from, out of, or in connection with the software or the use or other dealings in the software.
 */

#include <Indio.h>
#include <UC1701.h>

// Initialiser l'écran UC1701
static UC1701 lcd;

// Configuration des broches pour les boutons de façade
const int startButtonPin = 25; // Bouton A (Start)
const int resetButtonPin = 23; // Bouton B (Reset)
const int channel = 1;        // CH1 OUT (Canal 1 correspond à D22)
const unsigned long duration = 1 * 60 * 1000; // Durée totale : 1 minute en millisecondes // 
const unsigned long interval = 100; // Intervalle de mise à jour : 100 ms

// Variables globales
unsigned long startTime = 0;
bool isRunning = false;          // Indique si la séquence est en cours
float lastVoltage = 0.0;         // Dernière valeur affichée

void setup() {
  // Initialiser les broches pour les boutons de façade
  pinMode(startButtonPin, INPUT_PULLUP); // Configurer Bouton A en entrée avec pull-up
  pinMode(resetButtonPin, INPUT_PULLUP); // Configurer Bouton B en entrée avec pull-up

  // Initialiser la communication série
  Serial.begin(9600);

  // Initialiser l'écran UC1701
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Expo Voltage");

  // Initialiser la bibliothèque Indio avec une résolution de 16 bits
  Indio.begin(16);

  // Configurer CH1 OUT pour fonctionner en mode 10V (0-10V)
  Indio.analogWriteMode(channel, V10);

  // Réinitialiser la tension au démarrage
  resetSequence();
}

void loop() {
  // Vérifier l'état des boutons
  if (digitalRead(startButtonPin) == LOW && !isRunning) { // Bouton A (Start)
    startSequence();
  }

  if (digitalRead(resetButtonPin) == LOW) { // Bouton B (Reset)
    resetSequence();
  }

  // Si la séquence est en cours, continuer à générer la courbe exponentielle
  if (isRunning) {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - startTime;

    if (elapsedTime >= duration) {
      // Fin de la séquence, fixer à 10V
      Indio.analogWrite(channel, 10.0, false);
      displayVoltage(10.0);
      isRunning = false; // Arrêter la séquence
    } else {
      // Calculer et afficher la tension exponentielle
      float timeFraction = float(elapsedTime) / duration;
      float adjustedExp = exp(5 * timeFraction) - 1;
      float maxExpValue = exp(5) - 1;
      float voltageFraction = adjustedExp / maxExpValue;
      float voltage = voltageFraction * 10.0;

      // Sortie et affichage de la tension
      Indio.analogWrite(channel, voltage, false);
      displayVoltage(voltage);
    }

    delay(interval); // Pause avant la prochaine mise à jour
  }
}

// Fonction pour lancer la séquence
void startSequence() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Starting...");
  delay(500); // Pause visuelle
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Expo Voltage");
  startTime = millis(); // Démarrer la séquence
  isRunning = true;
}

// Fonction pour réinitialiser la séquence
void resetSequence() {
  Indio.analogWrite(channel, 0.0, false); // Réinitialiser la tension à 0V
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reset Complete");
  lcd.setCursor(0, 16);
  lcd.print("Voltage: 0.00 V");
  isRunning = false; // Arrêter la séquence
}

// Fonction pour afficher la tension
void displayVoltage(float voltage) {
  lcd.setCursor(0, 16);
  lcd.print("Voltage:       ");
  lcd.setCursor(0, 16);
  lcd.print("Voltage:");
  lcd.setCursor(64, 16);
  lcd.print("      ");
  lcd.setCursor(64, 16);
  lcd.print(String(voltage, 2) + " V");
}
