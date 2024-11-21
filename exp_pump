const int analogPin = 9; // Broche PWM
const unsigned long duration = 5 * 60 * 60 * 1000; // 5 heures en millisecondes
const unsigned long interval = 1000; // Intervalle de mise à jour en ms (1 seconde)
unsigned long startTime;

void setup() {
  pinMode(analogPin, OUTPUT);
  startTime = millis(); // Démarrer le chronomètre
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;

  // Vérifier si la durée de 5 heures est atteinte
  if (elapsedTime >= duration) {
    analogWrite(analogPin, 255); // Fixer à la tension maximale
    return;
  }

  // Normaliser le temps (0 à 5 heures = 0.0 à 5.0)
  float timeInHours = float(elapsedTime) / (60 * 60 * 1000); // Temps en heures (0 à 5)

  // Calculer la tension exponentielle
  float expValue = exp(timeInHours) - 1; // Fonction exponentielle décalée
  float maxExpValue = exp(5) - 1; // Maximum pour 5 heures
  float voltageFraction = expValue / maxExpValue; // Normaliser entre 0 et 1

  int pwmValue = int(voltageFraction * 255); // Convertir en échelle PWM (0-255)

  // Sortir la valeur PWM
  analogWrite(analogPin, pwmValue);

  delay(interval); // Attendre avant la prochaine mise à jour
}
