# Korskompilering

Korskompilering är svåra saker.

Har hittills använt miljö nedladdad från:
https://launchpad.net/gcc-arm-embedded/+download

prefix: arm-none-eabi-

Behövs: En portad libc, till RPi eller specifikt till mjukvarusystemet
som skall användas.

Det finns nåt som heter newlib. Vad jag förstått är den byggd så att man
enbart behöver implementera ett fåtal funktioner, för konsol-I/O bland annat.
Skall undersökas.
