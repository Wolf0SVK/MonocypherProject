# Historia zmien

## 19. December 2024

### Strukturalne zmeny
- Vytvorenie novych suborov:
  - crypto_utils.h a crypto_utils.c
  - siete.h a siete.c
  - constants.h
- Refaktoring zdielanych funkcii a konstant zo server.c a client.c do novych modulov
- Pridanie podpory pre Windows pomocou .bat suboru

### Bezpecnostne vylepsenia
- Zdokonalenie derivacie klucov pre client.c aj server.c
- Zjednotenie spravy kryptografickych materialov

### Sprava chyb
- Standardizacia chybovych hlaseni
- Prechod z fprint na fprintf pre konzistentne hlasenie chyb
- Vylepsena detekcia a sprava chyb v sietovej komunikacii

### Optimalizacie kodu
- Unifikacia nazvov funkcii napriec platformami
- Odstranenie duplicitneho kodu
- Zlepsena organizacia zdrojoveho kodu

### Kompatibilita
- Zjednotenie sietovych operacii
- Standardizacia systemovo-specifickych volani
