# Teil 1

## 1) Was sehen Sie nach der Ausführung des Programmes im Graphik-Fenster?
Nach der Ausführung des Programmes sehe ich ein rotes Quadrat in der Fenstermitte

## 2) Sind die Anweisungen glBegin und glEnd unbedingt notwendig? Was passiert, wenn￼man sie weglässt?
glBegin() und glEnd() umschließene die Eckpunkte einer Form

## 3) An welchen Positionen im Programm müssen diese glColor4f-Anweisungen stehen?
Nach glBegin() vor glVertext3f()

## 4) Welche Position im Code ist am besten zum Aufruf von glClear geeignet und warum?
Vor der glLoadIdentity(), da diese alles zurücksetzt

## 5) In welcher Reihenfolge müssen glClear und glClearColor aufgerufen werden?
Logischerweise muss zuerst glClear() aufgerufen werden, bevor glClearColor() aufgerufen wird. Sonst würde die gerade gesetzte Hintergrundfarbe direkt wieder gelöscht werden.

## 6) Was passiert, wenn Sie in einer Animation glClear(GL\_COLOR\_BUFFER\_BIT); weglassen? (Ihre Vermutung können Sie aber erst in Teil 4 überprüfen.)
Die verschiedenen Frames würden sich überlagern (?)

## 7) Welche der beiden Flächen sehen Sie?
Nur die grüne

## 8) Erzeugen Sie die Flächen mal in einer anderen Reihenfolge: Was fällt Ihnen auf und warum ist das so?
Die Fläche, die zuletzt gezeichnet wurde, überlagert alle anderen

## 9)
### a) Entspricht die Ansicht der Flächen nun Ihren Erwartungen?
Ja, wenn man die Fenstergröße verändert, verändert sich auch das View
### b) Beschreiben Sie kurz, wie der Z-Buffer funktioniert.
?

# Teil 2
## 10) Welche Fläche sehen Sie und warum sehen Sie gerade diese Fläche?
Man sieht die Rückseite, weil die Kamera vom Ursprung nach vorne schaut, also vom inneren des Würfels

## 11) Probieren Sie (ohne Translation des Würfels) die folgenden Kamerapositionen aus und dokumentieren Sie die dazu verwendeten gluLookAt-Aufrufe:
### a) Betrachtung der Szene von vorne oben; (Kameraposition: (0., 1., 1.). Sind die Parameterwerte in glOrtho richtig gesetzt? Falls NEIN, was stimmt nicht?
`gluLookAt ( 0., 1., 1., 0., 0., 0., 0., 1., 0.)`, `gnuOrtho` ist nicht richtig gesetzt, weil wir zu nah dran sind
### b) Betrachtung der Szene direkt von rechts; Kameraposition: (1., 0., 0.). Wie lauten die kompletten Aufrufe von glortho und gluLookAt?
`gluLookAt ( 1., 0., 0., 0., 0., 0., 0., 1., 0.)` und `glOrtho( -1., 1., -1., 1., 0.0, 3.0)`
### c) Betrachtung der Szene von rechts oben: wie lautet die Kameraposition: (?, ?, ?).
`gluLookAt ( 1., 1., 0., 0., 0., 0., 0., 1., 0.)`

### 12) Ist es möglich, den Rotate-Befehl vom „oberen“ Teil in die beiden Äste des Szenegraphs zu verlagern? (Wenn JA, wohin und wie? Wenn NEIN, warum nicht?)
Ja, nach den jeweiligen glPushMatrix Befehl

