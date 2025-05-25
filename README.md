Ce code est la deuxième partie du projet qui permet de piloter une bobine ( ou un moteur ) en intensité.
En effet, ce code permet à une carte Arduino Uno d'acquérir des informations d'une Méga ( ou autre carte ) par les pins TX et RX.
Ici, l'information est une distance.
De cette distance, on en déduit l'intensité nécessaire à la bobine pour la hauteur souhaitée et on pilote à travers le module MD04 (Datasheet : https://www.robot-electronics.co.uk/files/md04tech.pdf) la bobine.
