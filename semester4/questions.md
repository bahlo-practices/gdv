# Teil 1

1. Nach der Ausführung des Programmes sehe ich ein rotes Quadrat in der Fenstermitte
2. glBegin() und glEnd() werden zum rendern der Szene benötigt
3. Nach glBegin() vor glVertext3f()
4. Vor der glLoadIdentity()
5. Logischerweise muss zuerst glClear() aufgerufen werden, bevor glClearColor() aufgerufen wird. Sonst würde die gerade gesetzte Hintergrundfarbe direkt wieder gelöscht werden.
6. Die verschiedenen Frames würden sich überlagern
7. Nur die grüne
8. Die Fläche, die zuletzt gezeichnet wurde, überlagert alle anderen
9. a) Ja, wenn man die Fenstergröße verändert, verändert sich auch das View
   b)

# Teil 2
10. Man sieht die Rückseite, weil die Kamera so ausgerichtet ist
11. a) `gluLookAt ( 0., 1., 1., 0., 0., 0., 0., 1., 0.)`, `gnuOrtho` ist nicht richtig gesetzt, weil wir zu nah dran sind

