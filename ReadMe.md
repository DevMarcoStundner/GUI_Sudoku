# Sudoku

# Implementierte Funktionen
- Grundfunktionen von Sudoku sind implementiert

- Drei verschiedene Schwierigkeitsstufen Hard, Normal, Leicht
- je nach Schwierigkeitsstufe sind mehr oder weniger Felder aufgedeckt

- Die bereits eingesetzten Ziffern sind auf read-only

- Wenn der Spieler eine falsche Zahl eingibt wird diese nach dem Check rot 
- und bleibt solange rot bis die richtige Zahl eingegeben wird und wieder auf Check 
- gedrückt wird

- Es können nur Ziffern zwischen 1 bis 9 eingegben werden

- Wenn alle Felder richtig eingetragen sind und auf Check gedrückt wird kommt ein 
- Pop-Up Fenster mit der Benachrichtigung dass alles richtig ist

# Nicht implementierte Funktionen

- Es wurde zwar ein Timer implementiert jedoch funktioniert die Ausgabe in 
- der Infobar noch nicht

- Die Anzeige der fehlenden Felder sind auch noch nicht in der Infobar implementiert

- Super-easy mode wurde nicht implementiert

- Ein WARNING: invalid cast from 'GtkEntry' to 'GtkGrid'

- Ein CRITICAL: gtk_grid_attach: assertion 'GTK_IS_GRID (grid)' failed