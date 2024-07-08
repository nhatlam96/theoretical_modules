## Random Notes

- human, dev, set error. avoidable bias, variance
- increasing regularization decreases variance between training set error and dev set error

## Theorie
### Session 1
#### 0 quick overview
- Lineare Regression hingegen ist eine separate Methode für die Schätzung von kontinuierlichen Werten in Regressionsproblemen, relu als aktivierung
- Logistische Regression für binäre Klassifikationsprobleme, sigmoid als aktivierung
- Softmax Regression für Mehrklassen-Klassifikationsprobleme, softmax als aktivierung

#### 1.1 Klassifikation
- x1w1 + x2w2 + b = lineare Gerade im 2D Feld für Klassifikation
	- die Gewichte und das b werden solange angepasst, bis der Fehler minimal ist
  ![[Perzeptron.png]]
- wenn eine gerade nicht ausreicht, dann zusätzliche Geraden nehmen:![[Perzeptron_Zwei_Geraden.png]]
- supervised learning: modell mit already klassifizierten (labeled) datensätzen trainieren
- man kann anhand von relationen und gewichten der pixeln sehen, welche mit wem verwandt sind und diese dann in kategorien unterteilen, um dann zu klassifizieren ![[Layers_Weights.png]]
#### 1.2 Disrkiminierend vs Generativ
- diskriminierend == verurteilend: input of x -> model determines class
	- P(y|x) = what is y under the input of x. conditional probability
- generativ: input of x -> model learns distribution of data and produces new similiar datasets
	- P(x,y) = what are the chances that they are connected together? joint probability
	- A tin has height and radius as x, so we adjust their weights so that they look like a median or average tin
#### 1.3 Encoder-Decoder Architecture
- Encoder: converts input into numerical context vectors, so it reduces dimensions while preserving relationships between elements
- Decoder: uses attention mechanisms and applies them to the output of the encoder. so it weight certain elements and learns their patters across various datasets to generate better outputs that reflect the original input encoder data
- Basically: encoder rein, komprimieren, und dann raus

#### 1.4 Convert Words to Numericals
- Ein Wort mit einem 1 Dimensionalen Array ist nicht Ideal, da ein Wort mehrere Bedeutungen haben könnte.
	  ![[one_vector_per_word.png]]
- Für mehrere Bedeutungen können mehrere Vektoren hinzugefügt werden, also eine n-Dimensionalität pro Wort
	- ![[context_words.png]]

### Session 2
#### 2.1 Kostenfunktion
- mindestens
	- stetig = keine abgehackte Linie, sondern eine ganze
	- differenzierbar = keine Knicke, eine Steigung bzw. Tangente muss möglich sein
- idealerweise auch
	- kovex = funktionswerte unterhalb verbindungsgeraden xy
	- keine lokalen minima = es könnte sein, dass man dort stecken bleibt, deshalb besser wenn nur ein globales min existiert
- fehlerfunktion nicht stetig und differenzierbar, welche probleme gibt es?
	- der algorithmus versteht nicht, in welche richtung man gehen sollte für das lokale minimum
	- der algrithmus muss an einem beliebigen punkt die ableitung berechnen können für sprungrichtung und -weite, wenn er steil ist dann sprint er weiter, und wenn es steil ist dann springt er nicht so weit

#### 2.2 Overfitting
- Welchen Effekt hat es, wenn man in einem neuronalen Netz (a) die Anzahl der Eingangskonten erhöht bzw. (b) die Anzahl der versteckten Schichten erhöht?
	- mehr komplexere berechnungen durchführen
	- mehr features erkennen bzw. evtl. zu viele features erkennen, features die besser keine features sein sollten
- genug parameter sind vorraussetzung zu overfitting, und zu viel trainieren bzw. zu viele epochen führt dann dazu
- zu hohe varianz kann auch zu overfitting führen (Synonym?). fehler durch bias = varianz? also daten waren zu einseitig oder unpassend?
- mit early stopping kann man overfitting verhindern
- Lernt Daten zu genau, wie Rauschen oder Außreiser

#### 2.3 Optimizers
- gradient descent alone is not ideal, due to missing momentum or learning rate decay implemention from optimizers
	- Like Adam, they optimize the hyperparameters

- train set werden mit feed forward berechnet und mit back propagation die gewichte verbessert. nach jedem batch wird das dann über dev getestet wie gut es ist. testdaten nimmt man dann am schluss um dann die gesamt accuracy zu testen.

- gradient descent: wenn ich ein parameter ändere, inwiefern verändert es die Fehlerfunktion?

- kann gradient clipping verwenden um das exploding gradient zu verhindern
	- exploding gradient, bei relu möglich, da es unbegrenzt ins positive geht und durch multiplikationen zu sehr großen werte führen könnte. kann aber durch regulasierung von optimizern verhindert werden


### Session 4
#### 4.1 - Entscheidungsgrenze

- gerade Linie bei linearen Modellen wie logistische Regression
- hochdimensionierten Feature-Räume mindestens eine Fläche
- bei großen oder komplexen Datensätzen sollte ein tiefes neuronales Netz verwendet werden, um komplexere zusammenhänge besser verstehen zu können
- wird durch die backpropagation verbessert

#### 4.2 - Feed forward vs back propagation
#### Feed Forward
- **Prozess:** Daten fließen von der Eingabeschicht zur Ausgabeschicht.
- **Zweck:** Vorhersage mit aktuellen Gewichten und Biases.

#### Backpropagation
- **Prozess:** Fehler wird rückwärts durch das Netz propagiert.
- **Zweck:** Gradienten berechnen und mit Gradient Descent Gewichte und Biases anpassen.


### Session 6
#### 6.1 - Underfitting
- Nicht genug Parameter um die Trainingsdaten zu verstehen
	- zu wenig gelernt
- Fehler durch Bias, welches vllt zu einem zu stark vereinfachten Modell führt
#### 6.2 - Modellgröße
- lieber ein größeres Modell und dann diese anpassen
	- wie eine etwas größere hose kaufen und dann einen gürtel nehmen

#### 6.4 - Regularisierung
- extreme Gewichte sollten vermieden werden um vanishing oder exploding gradient zu vermeiden, normale werte fürhen zu effizienteren berechnungen
- mit Fehlerfunktionen kann man das regulieren indem man in der Formel ein Penalty hinzufügt

##### 6.4.1 - Dropout
- schaltet zufällige neuronen oder knoten ab, sollte das training mehr ausgeglichen machen und zu einer besseren generalisierung führen, weil dann potentielle biases vermieden werden können. es können nämlich während den epochen zu starke bereiche im neuronennetzwerk entstehen, welche dann das training zu arg dominieren

##### 6.4.2 - Early Stopping
- Gradient Descent (gewichte werden iterativ angepasst) bis die Fehler zu den Validierungsdaten zunehmen, dann wird das Training abgebrochen
	- ansonsten wenn man darüber geht, dann ist es ein anzeichen zu overfitting von den trainingsdaten

##### 6.4.3 - L1 und L2
- L1: Manche Gewichte gehen dann gegen 0, was zu vereinfachung des Modells führt und overfitting verhindert
- L2: Größere Gewichte werden runter gesetzt, so dass alle klein sind. das ist mehr preferred um mehr verteilte Daten zu haben 

#### 6.6 - Gradient Descent Typen
##### Batch Gradient Descent
- In jeder Epoche werden die gesamten Trainingsdaten durch das neuronale Netz gelaufen
Vorteile: Stabilere Berechnung der Gradienten, da es dann den gesamten Datensatz betrachtet
Nachteile: Umfangreichere Matrizenberechnung
##### Stochastic Gradient Descent
- Ein einzelnes Datum eines Trainingssatzes wird in einer Epoche verwendet
Vorteile: Schnelle Parameteraktualisierung
Nachteile: Ungenaues finales Minima
##### Mini Batch Gradient Descent
- Ein Teil des Trainingssatzes
Vorteile: Parallelisierung, schnellere Berechnung
Nachteile: Definieren der Batch Größe muss man noch herausfinden per Datensatz
##### Zufälliger Neustart
- random neustarts an mehreren Stellen während des gradient descents, um das beste globale Minimum zu finden

### Session 7-1
- Hyperparameters: Size and Number of Hidden Layers, Epochs, learning rate
- Parameters: weights, bias

### Session 7-2
- train dev test
	- its okay that train has different distro to dev and test
	- not okay when dev and test are different, because dev and test should have the same evaluation metrics to be comparable
- variance error = dev error - train error
- bias = low error percentages indicate low bias
- avoidable bias = bayes error - train error?


### Session 8
Aufgabe 1
- parameter: weights, bias (vom Modell bestimmt)
- hyperparameter: anzahl hidden layers, anzahl neuronen pro hidden layer, learning rate alpha (von uns festgelegt)

Aufgabe 2
- Fehlerfunktion: Misst die Abweichung zwischen Ydach und Y über einzelntes Trainingsbeispiel
- Kostenfunktion: Wie die Fehlerfunktion, aber sie betrachtet alle Trainingsdaten für die Evaluirung der durchschnitts-Gesamtleistung des Modells

Aufgabe 3
- Nominalskaliert: Qualitative Variablen ohne Rangskalierung
- Regression mit Nominalskalierten Variablen: Logistische Regression: Welche Produkte wird ein Kunde kaufen?

Aufgabe 4
- x = input, I = kostenfunktion, m = größe des trainingsdatensatzes, alpha = learning rate, b = bias, db = ableitung von bias, w = gewichte

Aufgabe 5
- gerade mit y_dach=wx+b

Aufgabe 6
- wenn zu klein = braucht zu lang
- wenn zu groß = instables lernen, mehrfaches überspringen des globalen minimums

Aufgabe 7
- Bei einer Lücke kann eine Ableitung nicht existieren und somit keine Richtung definiert werden
- differenzierbar = keine knicke, an einem Knick ist die Ableitung nicht definierbar, weil die Tangente so oder so angelegt werden könnte, da sind zwei Richtungen möglich
- stetig = in einer linie zeichbar

Aufgabe 9
sig(z) = 1 / 1 + e^-z
Die Werte werden von 0 bis 1 limitiert, gut für Wahrscheinlichkeitsberechnungen zu binären Klassifizierungsproblemen
- monoton steigend, stetig, differenzierbar, nicht linear

Aufgabe 10
Eingangsknoten = Dimension wird höher
- mehr Daten = bessere Ergebnisse
- weniger Daten = schnellere Ergebnisse
Hidden Layer = ermöglicht komplexere Entscheidungsgrenzen

Aufgabe 11
Feed Forward: Prozess, bei dem die Eingabedaten durch die verschiedenen Schichten eines neuronalen Netzes fließen, um eine Ausgabe zu erzeugen. 

Aufgabe 12
- **Binäre Klassifikation:** Zwei Klassen (z.B. Spam/Kein Spam), Aktivierungsfunktion: Sigmoid
- **Mehrklassen-Klassifikation:** Mehr als zwei Klassen (z.B. Handgeschriebene Ziffern 0-9), Aktivierungsfunktion: Softmax
- **Regression:** Vorhersage kontinuierlicher Werte (z.B. Hauspreise), Aktivierungsfunktion: Identitätsfunktion (keine spezielle Aktivierungsfunktion in der Ausgabeschicht).

## Notes 27 Jun
- logisitsche reg: 
	- y = mx +b; y wäre abhängig, weil es von x abhängig ist. dann ist m nur ein koeffizient und b eine konstante

- transponieren von matritzen? wozu?
	- für multiplizieren von zwei matritzen muss:
		- anzahl der spalten des ersten, muss die anzahl der zeilen des zweiten sein, damit sie miteinander verrechnet werden können. stimmt das?
	- wTx, w muss man transponieren wenn man eine matrix hat