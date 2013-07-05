# Att välja RTOS

Korskompileringsmiljön måste stödja stdio innan det kan bli kul.

## FreeRTOS

Finns portad till RPi. Vitt spridd, öppet API, fint.
Dock inte drivrutiner för någonting. Lyckats skriva till/läsa från UART, med
nöd och näppe.

## BitThunder

Bygger på FreeRTOS och från början skriven för RPi.
Använder den samma kernel API som FreeRTOS?
Svår att få igpng, på grund av korskompileringsmiljön.