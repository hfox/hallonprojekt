# Konsolkabel

För att ansluta via UART till Raspberry Pi.

RPis UART talar RS232 på 3,3 volt i 115200 baud. Många USB-RS232 arbetar på 5
volt. De två alternativen som finns är då att antingen använda en buffer som
drar upp/ner spänningen, eller att finna en USB-RS232 som arbetar på 3,3 volt.

## Spänningsomvandlare

(Att testa)

## 3,3 volt RS232

Den heter nåt och har följande pinout. Den har även 5 volt strömförsörjning.

Pin anger vilken pinne på RPis GPIO, färg anger vilken sladd på omvandlaren.

* Pin 2 (5 volt), RÖD (5 volt)
* Pin 4 (jord), SVART (jord)
* Pin 6 (RX), VIT (TX)
* Pin 8 (TX), GRÖN (RX)

## Programvara

Minicom. Skriv bra konfiguration här.
