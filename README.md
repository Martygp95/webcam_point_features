# webcam_point_features
Detection of ORB features from online webcam imges.

## Definició ORB

El ORB és una tècnica de processament de la imatge. La principal característica d'aquest mètode és la detecció de *features* o característiques, associant a cada característica amb un descriptor.

Les característiques es defineixen com a un conjunt de píxels de la imatge que tenen diferències respecte la mateixa quantitat de píxels del voltant. Per tant, la quantitat de pixels que primerament es podria definir com una característica, compara amb la mateixa quantitat de píxels en diferents direccions (com aplicar una màscara). A partir d'aquesta comparació, es determina la quantitat d'error que existeix entre les dues imatges; si aquesta quantitat d'error és gran i a més, aquest error també és gran en diverses direccions, permet determinar que la característica és vàlida. 
Per exemple, les cantonades d'un objecte poden ser característiques vàlides, ja que es diferencien clarament de la resta de píxels i en diverses direccions, o per exemple objectes que tinguin forma de circumferència.

Aquesta definició és simple, degut a que per tal de definir amb més precisió les característiques vàlides, s'han de fer més operacions matemàtiques que van més enllà del error.

A cada característica se li atribueix un descriptor, que simplement descriu la característica. D'aquesta manera, es poden trobar característiques que tinguin el mateix descriptor, la qual cosa permet trobar semblances entre objectes. 

## Màscara (codi)

Una màscara actúa com a filtre per tal de processar únicament una part de la imatge. En aquest codi l'objectiu és detectar característiques a cada part de la imatge, utilitzant una màscara que anirà agafant parts de la imatge dividides en 12 divisions (3x4). La màscara s'inicialitza primer amb zeros, amb la mateixa dimensió que la imatge (480x640 píxels). Per tal de que la màscara tingui efecte sobre la regió que volem en cada moment, aquesta regió s'ha d'emplenar amb números de 255, per tal de que la funció actui sobre aquesta regió. Per a cada regió es processa la imatge i es detecten caracteŕístiques de la imatge.

## Referències 

*CVFX Lecture 9: Feature Detectors*
https://www.youtube.com/watch?v=9-F5-gUIAWE
